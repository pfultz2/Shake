
#include "extract.h"
#include "resource_ptr.h"
#include "merge_path.h"
#include <exception>
#include <string>
#include <archive.h>
#include <archive_entry.h>

namespace shake {

void destroy_read_archive(struct archive* ar)
{
    archive_read_close(ar);
    archive_read_free(ar);
}

using archive_read_ptr = resource_ptr<struct archive, &destroy_read_archive>;

archive_read_ptr read_archive(const std::string& name)
{
    auto a = archive_read_ptr(archive_read_new());
    archive_read_support_format_all(a.get());
    archive_read_support_compression_all(a.get());

    int r = archive_read_open_filename(a.get(), name.c_str(), 10240);
    if (r) throw std::runtime_error("Can't open archive");

    return a;
}

void destroy_write_archive(struct archive* ar)
{
    archive_write_close(ar);
    archive_write_free(ar);
}
using archive_write_ptr = resource_ptr<struct archive, &destroy_write_archive>;

archive_write_ptr write_archive()
{
    auto a = archive_write_ptr(archive_write_disk_new());
    archive_write_disk_set_options(a.get(), ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);
    archive_write_disk_set_standard_lookup(a.get());
    return a;
}

template<class A>
void throw_archive_error(A& a)
{
    throw std::runtime_error(archive_error_string(a.get()));
}

struct archive_entry* read_next_entry(archive_read_ptr& a)
{
    struct archive_entry* entry;
    int r = archive_read_next_header(a.get(), &entry);
    if (r == ARCHIVE_EOF) return nullptr;
    if (r < ARCHIVE_WARN) throw_archive_error(a);
    return entry;
}

void copy_archive_data(archive_read_ptr& ar, archive_write_ptr& aw)
{
    const void *buff;
    size_t size;
    off_t offset;

    for (;;) 
    {
        int r1 = archive_read_data_block(ar.get(), &buff, &size, &offset);
        if (r1 == ARCHIVE_EOF) return;
        if (r1 < ARCHIVE_WARN) throw_archive_error(ar);

        int r2 = archive_write_data_block(aw.get(), buff, size, offset);
        if (r2 < ARCHIVE_WARN) throw_archive_error(ar);
    }
}

void extract_to(const std::string& name, const std::string& dir)
{
    archive_read_ptr ar = read_archive(name);
    archive_write_ptr out = write_archive();
    struct archive_entry *entry;
    while((entry = read_next_entry(ar)))
    {
        // archive_entry_pathname
        archive_entry_set_pathname(entry, merge_path(dir, archive_entry_pathname(entry)).c_str());
        int r1 = archive_write_header(out.get(), entry);
        if (r1 == ARCHIVE_OK) copy_archive_data(ar, out);

        int r2 = archive_write_finish_entry(out.get());
        if (r2 < ARCHIVE_WARN) throw_archive_error(out);
    }
}

}