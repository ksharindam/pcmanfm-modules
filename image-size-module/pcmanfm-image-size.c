/*
pcmanfm-image-size.c

Copyright (C) 2019 Arindam Chaudhuri <ksharindam@gmail.com>
*/

#include <libfm/fm.h>
#include <pcmanfm-modules.h>
#include "imagesize.h"

FM_DEFINE_MODULE(tab_page_status, image_size)


static char * image_size_sel_message(FmFileInfoList *files, gint n_files) {
    // return if more than 1 file is selected
	if (n_files>1) return 0;
    // return if not image
	FmFileInfo* info = fm_file_info_list_peek_head(files);
	if (! fm_file_info_is_image(info)) return 0;
    // return when file can not be read
    char * path_str = fm_path_to_str(fm_file_info_get_path(info));
    FILE *file = fopen(path_str,"rb");
    g_free(path_str);
    if (!file) return 0;

    if (isJpeg(file) || isPng(file)) {
        int width=0, height=0;
        int ok = imgsize(file, &width, &height);
        if (ok) {
            char *msg = g_malloc(64);
            msg[0]=0;
            snprintf(msg, 64, "( %dx%d )", width, height);
            fclose(file);
            return msg;
        }
    }
    fclose(file);
    return 0;
}


FmTabPageStatusInit fm_module_init_tab_page_status = {
	.init = NULL,
	.finalize = NULL,
	.sel_message = image_size_sel_message
};

