#include <glib.h>
#include <glib/gprintf.h>

gint compare_func(gconstpointer a, gconstpointer b, gpointer userdata) {
	return (gint)g_hash_table_lookup(userdata, b) - (gint)g_hash_table_lookup(userdata, a);
}

void print(gpointer data, gpointer userdata) {
	g_printf("%s %d\n", data, (gint)g_hash_table_lookup(userdata, data));
}

void key_destroy_func(gpointer data) {
	g_free(data);
}
