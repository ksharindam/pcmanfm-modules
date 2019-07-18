#include <pcmanfm-modules.h>
#include <string.h>

FM_DEFINE_MODULE(tab_page_status, symlink_target)

static char *get_symlink_target(FmFileInfoList *files, gint n_files)
{
  FmFileInfo *fi = fm_file_info_list_peek_head(files);
  if (n_files > 1 || !fm_file_info_is_symlink(fi))
    return NULL;
  return g_strdup_printf("--> %s", fm_file_info_get_target(fi));
}

FmTabPageStatusInit fm_module_init_tab_page_status = {
  NULL,
  NULL,
  .sel_message = get_symlink_target
};
