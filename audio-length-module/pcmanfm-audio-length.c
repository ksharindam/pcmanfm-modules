#include <stdlib.h>
#include <libfm/fm.h>
#include <pcmanfm-modules.h>
#include <taglib/tag_c.h>

FM_DEFINE_MODULE(tab_page_status, audio_length)


static char *get_audio_len(FmFileInfoList *files, gint n_files){

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

	if (TL_file != NULL) {
		if(taglib_file_is_valid(TL_file)){
			const TagLib_AudioProperties *TL_props = taglib_file_audioproperties( TL_file );
			length = taglib_audioproperties_length( TL_props );
			if( length>3600 ){
				audio_len = g_strdup_printf( "  --> %d:%02d:%02d", length/3600, (length%3600)/60, length%60 );
			}else{
				audio_len = g_strdup_printf( "  --> %d:%02d", length/60, length%60 );
			}

			taglib_tag_free_strings();
			taglib_file_free( TL_file );
			return audio_len;
		}
	}
	return NULL;
};


FmTabPageStatusInit fm_module_init_tab_page_status = {
  NULL,
  NULL,
  .sel_message = get_audio_len
};
