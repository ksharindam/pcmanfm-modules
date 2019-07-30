#include <stdlib.h>
#include <dlfcn.h>
#include <pcmanfm-modules.h>
//#include <poppler/glib/poppler-document.h>

typedef void PopplerDocument;

void* poppler;
PopplerDocument* (*poppler_document_new_from_file)(char*, char*/*passwd*/, GError**);
int (*poppler_document_get_n_pages)(PopplerDocument*);


FM_DEFINE_MODULE( tab_page_status, pdf_pages )

static gboolean _init_module()
{
    poppler = dlopen("libpoppler-glib.so.8", RTLD_LAZY);
    if (!poppler)
        return 0;
    poppler_document_new_from_file = dlsym(poppler, "poppler_document_new_from_file");
    poppler_document_get_n_pages = dlsym(poppler, "poppler_document_get_n_pages");
    return 1;
}

static void _finish_module()
{
    dlclose(poppler);
}

static char *_sel_message( FmFileInfoList *files, gint n_files )
{
	if ( n_files > 1)
		return 0;

	FmFileInfo *fi = fm_file_info_list_peek_head( files );
	const char* mimetype = fm_mime_type_get_type( fm_file_info_get_mime_type( fi ) );
	if ( strcmp( mimetype, "application/pdf" ) != 0 ){
		return 0;
	}

	char* filename;
	PopplerDocument* document;
	GError *error = NULL;
	int num_pages = 0;

	filename = fm_path_to_uri( fm_file_info_get_path( fi ) );
	document = poppler_document_new_from_file( filename, NULL, &error );
	if (error != NULL)
	{
		fprintf (stderr, "statusbar-pdf-pages error: %s\n", error->message);
		g_error_free( error );
	}
	free( filename );
	if (document == NULL) {
		return 0;
	}
	num_pages = poppler_document_get_n_pages( document );
	g_object_unref(document);

	if (num_pages == 1) {
		return g_strdup(" ( 1 page )");
	}
    return g_strdup_printf(" ( %i pages )", num_pages);
}

FmTabPageStatusInit fm_module_init_tab_page_status = {
    _init_module,
    _finish_module,
    _sel_message
};
