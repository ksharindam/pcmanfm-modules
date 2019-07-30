#include <stdlib.h>
#include <dlfcn.h>
#include <libfm/fm.h>
#include <pcmanfm-modules.h>
//#include <taglib/tag_c.h>

FM_DEFINE_MODULE(tab_page_status, audio_length)

typedef void TagLib_File;
typedef void TagLib_AudioProperties;

void *taglib;
TagLib_File* (*taglib_file_new)(char*);
int (*taglib_file_is_valid)(TagLib_File*);
TagLib_AudioProperties* (*taglib_file_audioproperties)(TagLib_File*);
int (*taglib_audioproperties_length)(TagLib_AudioProperties*);
void (*taglib_tag_free_strings)();
void (*taglib_file_free)(TagLib_File*);

static gboolean _init_module()
{
    taglib = dlopen("libtag_c.so.0", RTLD_LAZY);
    if (!taglib)
        return 0;
    taglib_file_new = dlsym(taglib, "taglib_file_new");
    taglib_file_is_valid = dlsym(taglib, "taglib_file_is_valid");
    taglib_file_audioproperties = dlsym(taglib, "taglib_file_audioproperties");
    taglib_audioproperties_length = dlsym(taglib, "taglib_audioproperties_length");
    taglib_tag_free_strings = dlsym(taglib, "taglib_tag_free_strings");
    taglib_file_free = dlsym(taglib, "taglib_file_free");
    return 1;
}

static void _finish_module()
{
    dlclose(taglib);
}

static char* _get_audio_len(FmFileInfoList *files, gint n_files){

    FmFileInfo *fi = fm_file_info_list_peek_head(files);
    if (n_files > 1 )
      return NULL;

	char* filename;
	int length;
	char *audio_len = "00:00";
	TagLib_File *TL_file;

	filename = fm_path_to_str( fm_file_info_get_path(fi) );
	TL_file = taglib_file_new( filename );
	free( filename );

	if ((TL_file == NULL) || (!taglib_file_is_valid(TL_file))) {
        taglib_file_free( TL_file );
        return NULL;
    }
    TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file );
    length = taglib_audioproperties_length( TL_props );
    if ( length>3600 ) {
        audio_len = g_strdup_printf( "  --> %d:%02d:%02d", length/3600, (length%3600)/60, length%60 );
    } else {
        audio_len = g_strdup_printf( "  --> %d:%02d", length/60, length%60 );
    }

    taglib_tag_free_strings();
    taglib_file_free( TL_file );
    return audio_len;
};


FmTabPageStatusInit fm_module_init_tab_page_status = {
    _init_module,
    _finish_module,
    _get_audio_len
};
