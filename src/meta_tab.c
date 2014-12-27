/*******************************************************************************#
#           guvcview              http://guvcview.sourceforge.net               #
#                                                                               #
#           Ilya Juhnowski <juhnowski@gmail.com>                                #
#                                                                               #
# This program is free software; you can redistribute it and/or modify          #
# it under the terms of the GNU General Public License as published by          #
# the Free Software Foundation; either version 2 of the License, or             #
# (at your option) any later version.                                           #
#                                                                               #
# This program is distributed in the hope that it will be useful,               #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 #
# GNU General Public License for more details.                                  #
#                                                                               #
# You should have received a copy of the GNU General Public License             #
# along with this program; if not, write to the Free Software                   #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA     #
#                                                                               #
********************************************************************************/
#include <glib.h>
#include <glib/gprintf.h>
/* support for internationalization - i18n */
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include "globals.h"
#include "callbacks.h"
#include "v4l2uvc.h"
#include "snd_devices.h"
#include "acodecs.h"
#include "../config.h"


static void
ximu_properties_dialog(GtkButton * CodecButt, struct ALL_DATA *all_data)
{
  struct GWIDGET *gwidget = all_data->gwidget;
  GtkTextIter start, end;
  GtkTextIter iter;

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
      gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
      gtk_window_set_title(GTK_WINDOW(window), "xIMU incoming data");
      gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);

  //-------------------------tool bar--------------------------------------------
  GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  GtkToolItem *startBtn = gtk_tool_button_new_from_stock(GTK_STOCK_OK);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), startBtn, -1);

  GtkToolItem *stopBtn = gtk_tool_button_new_from_stock(GTK_STOCK_CANCEL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), stopBtn, -1);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  GtkWidget *view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

  gwidget->ximu_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_create_tag(gwidget->ximu_buffer, "gap", "pixels_above_lines", 30, NULL);
    gtk_text_buffer_create_tag(gwidget->ximu_buffer, "lmarg", "left_margin", 5, NULL);
    gtk_text_buffer_create_tag(gwidget->ximu_buffer, "blue_fg", "foreground", "blue", NULL); 
    gtk_text_buffer_get_iter_at_offset(gwidget->ximu_buffer, &iter, 0);

    gtk_text_buffer_insert_with_tags_by_name(gwidget->ximu_buffer, &iter, "x-IMU test output\n", -1, "blue_fg", "lmarg",  NULL);
    gtk_text_buffer_insert(gwidget->ximu_buffer, &iter, "Waiting...\n", -1);

  GtkWidget *statusbar = gtk_statusbar_new();
      gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
      update_statusbar(gwidget->ximu_buffer, GTK_STATUSBAR (statusbar));

  gtk_container_add(GTK_CONTAINER(window), vbox);

 
  g_signal_connect(G_OBJECT(startBtn), "clicked", 
        G_CALLBACK(xImu_startBtn_clicked), all_data);
  
  g_signal_connect(G_OBJECT(stopBtn), "clicked", 
        G_CALLBACK(xImu_stopBtn_clicked), all_data);
  
  gtk_widget_show_all(window);

}


static void
tenso_properties_dialog(GtkButton * CodecButt, struct ALL_DATA *all_data)
{
  struct GWIDGET *gwidget = all_data->gwidget;
  GtkTextIter start, end;
  GtkTextIter iter;

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
      gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
      gtk_window_set_title(GTK_WINDOW(window), "Tenso incoming data");
      gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);

  //-------------------------tool bar--------------------------------------------
  GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  GtkToolItem *startBtn = gtk_tool_button_new_from_stock(GTK_STOCK_OK);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), startBtn, -1);

  GtkToolItem *stopBtn = gtk_tool_button_new_from_stock(GTK_STOCK_CANCEL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), stopBtn, -1);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  GtkWidget *view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

  gwidget->tenso_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_create_tag(gwidget->tenso_buffer, "gap", "pixels_above_lines", 30, NULL);
    gtk_text_buffer_create_tag(gwidget->tenso_buffer, "lmarg", "left_margin", 5, NULL);
    gtk_text_buffer_create_tag(gwidget->tenso_buffer, "blue_fg", "foreground", "blue", NULL); 
    gtk_text_buffer_get_iter_at_offset(gwidget->tenso_buffer, &iter, 0);

    gtk_text_buffer_insert_with_tags_by_name(gwidget->tenso_buffer, &iter, "Tenso test output\n", -1, "blue_fg", "lmarg",  NULL);
    gtk_text_buffer_insert(gwidget->tenso_buffer, &iter, "Waiting...\n", -1);

  GtkWidget *statusbar = gtk_statusbar_new();
      gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
      update_statusbar(gwidget->tenso_buffer, GTK_STATUSBAR (statusbar));

  gtk_container_add(GTK_CONTAINER(window), vbox);

 
  g_signal_connect(G_OBJECT(startBtn), "clicked", 
        G_CALLBACK(tenso_startBtn_clicked), all_data);
  
  g_signal_connect(G_OBJECT(stopBtn), "clicked", 
        G_CALLBACK(tenso_stopBtn_clicked), all_data);
  
  gtk_widget_show_all(window);

}

static void
encoder_properties_dialog(GtkButton * CodecButt, struct ALL_DATA *all_data)
{
  struct GWIDGET *gwidget = all_data->gwidget;
  GtkTextIter start, end;
  GtkTextIter iter;

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
      gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
      gtk_window_set_title(GTK_WINDOW(window), "Encoder incoming data");
      gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);

  //-------------------------tool bar--------------------------------------------
  GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  GtkToolItem *startBtn = gtk_tool_button_new_from_stock(GTK_STOCK_OK);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), startBtn, -1);

  GtkToolItem *stopBtn = gtk_tool_button_new_from_stock(GTK_STOCK_CANCEL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), stopBtn, -1);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  GtkWidget *view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

  gwidget->encoder_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_create_tag(gwidget->encoder_buffer, "gap", "pixels_above_lines", 30, NULL);
    gtk_text_buffer_create_tag(gwidget->encoder_buffer, "lmarg", "left_margin", 5, NULL);
    gtk_text_buffer_create_tag(gwidget->encoder_buffer, "blue_fg", "foreground", "blue", NULL); 
    gtk_text_buffer_get_iter_at_offset(gwidget->encoder_buffer, &iter, 0);

    gtk_text_buffer_insert_with_tags_by_name(gwidget->encoder_buffer, &iter, "Encoder test output\n", -1, "blue_fg", "lmarg",  NULL);
    gtk_text_buffer_insert(gwidget->encoder_buffer, &iter, "Waiting...\n", -1);

  GtkWidget *statusbar = gtk_statusbar_new();
      gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
      update_statusbar(gwidget->encoder_buffer, GTK_STATUSBAR (statusbar));

  gtk_container_add(GTK_CONTAINER(window), vbox);

 
  g_signal_connect(G_OBJECT(startBtn), "clicked", 
        G_CALLBACK(encoder_startBtn_clicked), all_data);
  
  g_signal_connect(G_OBJECT(stopBtn), "clicked", 
        G_CALLBACK(encoder_stopBtn_clicked), all_data);
  
  gtk_widget_show_all(window);

}


void
update_statusbar(GtkTextBuffer *buffer,
    GtkStatusbar  *statusbar)
{
    gchar *msg;
    gint row, col;
    GtkTextIter iter;

    gtk_statusbar_pop(statusbar, 0); 

    gtk_text_buffer_get_iter_at_mark(buffer,
	&iter, gtk_text_buffer_get_insert(buffer));

    row = gtk_text_iter_get_line(&iter);
    col = gtk_text_iter_get_line_offset(&iter);

    msg = g_strdup_printf("Chunck received: %d", row-5);

    gtk_statusbar_push(statusbar, 0, msg);

    g_free(msg);
}


void meta_tab(struct ALL_DATA *all_data)
{
	struct GLOBAL *global = all_data->global;
	struct GWIDGET *gwidget = all_data->gwidget;
	struct paRecordData *pdata = all_data->pdata;

	int line = 0;
	int i = 0;
	//TABLE
	GtkWidget *table3 = gtk_grid_new();
	  gtk_grid_set_column_homogeneous (GTK_GRID(table3), FALSE);
	  gtk_widget_set_hexpand (table3, TRUE);
	  gtk_widget_set_halign (table3, GTK_ALIGN_FILL);
	
	  gtk_grid_set_row_spacing (GTK_GRID(table3), 4);
	  gtk_grid_set_column_spacing (GTK_GRID (table3), 4);
	  gtk_container_set_border_width (GTK_CONTAINER (table3), 2);
	  gtk_widget_show (table3);
	
	//SCROLL
	GtkWidget *scroll3 = gtk_scrolled_window_new(NULL,NULL);
	
	//ADD TABLE TO SCROLL
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll3),table3);
	gtk_scrolled_window_set_placement(GTK_SCROLLED_WINDOW(scroll3), GTK_CORNER_TOP_LEFT);
	gtk_widget_show(scroll3);
	
	//new grid for tab label and icon
	GtkWidget *Tab3 = gtk_grid_new();
	  GtkWidget *Tab3Label = gtk_label_new(_("Meta Controls"));
	    gtk_widget_show (Tab3Label);

	  gchar* Tab3IconPath = g_strconcat (PACKAGE_DATA_DIR,"/pixmaps/guvcview/meta_controls.png",NULL);

	  GtkWidget *Tab3Icon = gtk_image_new_from_file(Tab3IconPath);
	    g_free(Tab3IconPath);
	    gtk_widget_show (Tab3Icon);
	    gtk_grid_attach (GTK_GRID(Tab3), Tab3Icon, 0, 0, 1, 1);
	    gtk_grid_attach (GTK_GRID(Tab3), Tab3Label, 1, 0, 1, 1);
	    
	gtk_widget_show (Tab3);
	
	//ADD SCROLL to NOTEBOOK (TAB)
	gtk_notebook_append_page(GTK_NOTEBOOK(gwidget->boxh),scroll3,Tab3);

	//enable meta
	line++;
	gwidget->MetaEnableCB=gtk_check_button_new_with_label (_(" Meta"));
	gtk_grid_attach(GTK_GRID(table3), gwidget->MetaEnableCB, 1, 0, 1, 1);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwidget->MetaEnableCB),  global->Meta_enable);
	gtk_widget_show (gwidget->MetaEnableCB);
	g_signal_connect (GTK_CHECK_BUTTON(gwidget->MetaEnableCB), "toggled",
		G_CALLBACK (MetaEnable_changed), all_data);
    

	line++;
	
	gwidget->label_XImuDevice = gtk_label_new(_("xIMU Device:"));//label_SndAPI
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_XImuDevice), 1, 0.5);

	gtk_grid_attach (GTK_GRID(table3), gwidget->label_XImuDevice, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_XImuDevice);
	
	gwidget->XImuDeviceCB = gtk_combo_box_text_new (); //SndAPI
	gtk_widget_set_halign (gwidget->XImuDeviceCB, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand (gwidget->XImuDeviceCB, TRUE);
	gtk_grid_attach(GTK_GRID(table3), gwidget->XImuDeviceCB, 1, line, 1, 1);
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->XImuDeviceCB),_("None"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->XImuDeviceCB),_("/dev/ttyUSB0"));
	gtk_widget_show (gwidget->XImuDeviceCB);
	gtk_combo_box_set_active(GTK_COMBO_BOX(gwidget->XImuDeviceCB),global->XImuDeviceCB_idx);//Sound_API
	gtk_widget_set_sensitive (gwidget->XImuDeviceCB, TRUE);
	g_signal_connect (GTK_COMBO_BOX_TEXT(gwidget->XImuDeviceCB), "changed", G_CALLBACK (XImuDeviceCB_changed), all_data);

	gwidget->XImuPropBtn= gtk_button_new_with_label (_("properties"));
	gtk_grid_attach (GTK_GRID(table3), gwidget->XImuPropBtn, 2, line, 1, 1);
	gtk_widget_show (gwidget->XImuPropBtn);
	g_signal_connect (GTK_BUTTON(gwidget->XImuPropBtn), "clicked", G_CALLBACK (ximu_properties_dialog), all_data);

	line++;
	
	gwidget->label_EncoderDevice = gtk_label_new(_("Encoder Device:"));
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_EncoderDevice), 1, 0.5);
	gtk_grid_attach (GTK_GRID(table3), gwidget->label_EncoderDevice, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_EncoderDevice);
//---
	gwidget->EncoderDeviceCB = gtk_combo_box_text_new ();//SndDevice
	
	gtk_widget_set_halign (gwidget->EncoderDeviceCB, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand (gwidget->EncoderDeviceCB, TRUE);
	gtk_grid_attach(GTK_GRID(table3), gwidget->EncoderDeviceCB, 1, line, 1, 1);

	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->EncoderDeviceCB),_("None"));
//TODO: request available encoder, now I have only one id=271264
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->EncoderDeviceCB),_("271264"));
	gtk_widget_show (gwidget->EncoderDeviceCB);

	gtk_combo_box_set_active(GTK_COMBO_BOX(gwidget->EncoderDeviceCB),global->EncoderDeviceCB_idx);

	g_signal_connect (GTK_COMBO_BOX_TEXT(gwidget->EncoderDeviceCB), "changed",
		G_CALLBACK (EncoderDeviceCB_changed), all_data);

gwidget->EncoderPropBtn= gtk_button_new_with_label (_("properties"));
gtk_grid_attach (GTK_GRID(table3), gwidget->EncoderPropBtn, 2, line, 1, 1);
gtk_widget_show (gwidget->EncoderPropBtn);
g_signal_connect (GTK_BUTTON(gwidget->EncoderPropBtn), "clicked", G_CALLBACK (encoder_properties_dialog), all_data);
    
//---	
	line++;
	gwidget->EncoderRateCB= gtk_combo_box_text_new ();//SndSampleRate
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->EncoderRateCB),_("Dev. Default"));
	gtk_widget_set_halign (gwidget->EncoderRateCB, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand (gwidget->EncoderRateCB, TRUE);
	gtk_grid_attach(GTK_GRID(table3), gwidget->EncoderRateCB, 1, line, 1, 1);
	gtk_widget_show (gwidget->EncoderRateCB);
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(gwidget->EncoderRateCB),global->EncoderRateCB_idx);
	g_signal_connect (GTK_COMBO_BOX_TEXT(gwidget->EncoderRateCB), "changed", G_CALLBACK (EncoderRateCB_changed), all_data);
	gwidget->label_EncoderRate = gtk_label_new(_("Encoder Rate:"));
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_EncoderRate), 1, 0.5);
	gtk_grid_attach (GTK_GRID(table3), gwidget->label_EncoderRate, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_EncoderRate);
	
	//channels
	line++;
//TODO: request available bridge, now I have only one id=253523
	gwidget->TensoDeviceCB= gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoDeviceCB),_("None"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoDeviceCB),_("253523"));
	
	gtk_widget_set_halign (gwidget->TensoDeviceCB, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand (gwidget->TensoDeviceCB, TRUE);
	gtk_grid_attach(GTK_GRID(table3), gwidget->TensoDeviceCB, 1, line, 1, 1);
	gtk_widget_show (gwidget->TensoDeviceCB);
	gtk_combo_box_set_active(GTK_COMBO_BOX(gwidget->TensoDeviceCB),global->TensoDeviceCB_idx);
	
	g_signal_connect (GTK_COMBO_BOX_TEXT(gwidget->TensoDeviceCB), "changed", G_CALLBACK (TensoDeviceCB_changed), all_data);
	
	gwidget->label_TensoDeviceCB = gtk_label_new(_("Tensor Device:"));
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_TensoDeviceCB), 1, 0.5);
	gtk_grid_attach (GTK_GRID(table3), gwidget->label_TensoDeviceCB, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_TensoDeviceCB);
    
        gwidget->TensoPropBtn= gtk_button_new_with_label (_("properties"));
        gtk_grid_attach (GTK_GRID(table3), gwidget->TensoPropBtn, 2, line, 1, 1);
        gtk_widget_show (gwidget->TensoPropBtn);
        g_signal_connect (GTK_BUTTON(gwidget->TensoPropBtn), "clicked", G_CALLBACK (tenso_properties_dialog), all_data);

	line++;
	gwidget->TensoRateCB = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB),_("8"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB),_("16"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB),_("32"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB),_("64"));
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB),_("128"));

	gtk_combo_box_set_active(GTK_COMBO_BOX(gwidget->TensoRateCB), global->TensoDeviceCB_idx);
	
	g_signal_connect (GTK_COMBO_BOX_TEXT(gwidget->TensoRateCB), "changed", G_CALLBACK (TensoRateCB_changed), all_data);

	gtk_widget_set_halign (gwidget->TensoRateCB, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand (gwidget->TensoRateCB, TRUE);
	gtk_grid_attach(GTK_GRID(table3), gwidget->TensoRateCB, 1, line, 1, 1);
	gtk_widget_show (gwidget->TensoRateCB);
	
	gwidget->label_TensoRateCB = gtk_label_new(_("Sensor Rate:"));
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_TensoRateCB), 1, 0.5);
	gtk_grid_attach (GTK_GRID(table3), gwidget->label_TensoRateCB, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_TensoRateCB);
	
//---------------------------------------------------------------------------------------------------
	
line++;
	gwidget->label_TensoChannels = gtk_label_new(_("Sensor Channels:"));
	gtk_misc_set_alignment (GTK_MISC (gwidget->label_TensoChannels), 1, 0.5);
	gtk_grid_attach (GTK_GRID(table3), gwidget->label_TensoChannels, 0, line, 1, 1);
	gtk_widget_show (gwidget->label_TensoChannels);
	
	
	gwidget->table_TensoChannels = gtk_grid_new();
	  gtk_grid_set_row_spacing (GTK_GRID (gwidget->table_TensoChannels), 4);
	  gtk_grid_set_column_spacing (GTK_GRID (gwidget->table_TensoChannels), 4);
	  gtk_container_set_border_width (GTK_CONTAINER (gwidget->table_TensoChannels), 4);
	  gtk_widget_set_size_request (gwidget->table_TensoChannels, -1, -1);
	  gtk_widget_set_halign (gwidget->table_TensoChannels, GTK_ALIGN_FILL);
	  gtk_widget_set_hexpand (gwidget->table_TensoChannels, TRUE);
	  gtk_grid_attach (GTK_GRID(table3), gwidget->table_TensoChannels, 1, line, 3, 1);
	  gtk_widget_show (gwidget->table_TensoChannels);

	// 0
	  gwidget->TensoChannTB_0 = gtk_check_button_new_with_label (_(" 0"));
	    g_object_set_data (G_OBJECT (gwidget->TensoChannTB_0), "effect_info", GINT_TO_POINTER(CH_0));
	    gtk_widget_set_halign (gwidget->TensoChannTB_0, GTK_ALIGN_FILL);
	    gtk_widget_set_hexpand (gwidget->TensoChannTB_0, TRUE);
	    gtk_grid_attach(GTK_GRID(gwidget->table_TensoChannels), gwidget->TensoChannTB_0, 1, 0, 1, 1);
	    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwidget->TensoChannTB_0),global->tenso_enabled_ch_0);
	    gtk_widget_show (gwidget->TensoChannTB_0);
	    g_signal_connect (GTK_CHECK_BUTTON(gwidget->TensoChannTB_0), "toggled", G_CALLBACK (TensoChannTB_0_changed), all_data);

	// 1
	  gwidget->TensoChannTB_1 = gtk_check_button_new_with_label (_(" 1"));
	    g_object_set_data (G_OBJECT (gwidget->TensoChannTB_1), "effect_info", GINT_TO_POINTER(CH_1));
	    gtk_widget_set_halign (gwidget->TensoChannTB_1, GTK_ALIGN_FILL);
	    gtk_widget_set_hexpand (gwidget->TensoChannTB_1, TRUE);
	    gtk_grid_attach(GTK_GRID(gwidget->table_TensoChannels), gwidget->TensoChannTB_1, 2, 0, 1, 1);
	    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwidget->TensoChannTB_1),global->tenso_enabled_ch_1);
	    gtk_widget_show (gwidget->TensoChannTB_1);
	    g_signal_connect (GTK_CHECK_BUTTON(gwidget->TensoChannTB_1), "toggled", G_CALLBACK (TensoChannTB_1_changed), all_data);

	// 2
	  gwidget->TensoChannTB_2 = gtk_check_button_new_with_label (_(" 2"));
	    g_object_set_data (G_OBJECT (gwidget->TensoChannTB_2), "effect_info", GINT_TO_POINTER(CH_2));
	    gtk_widget_set_halign (gwidget->TensoChannTB_2, GTK_ALIGN_FILL);
	    gtk_widget_set_hexpand (gwidget->TensoChannTB_2, TRUE);
	    gtk_grid_attach(GTK_GRID(gwidget->table_TensoChannels), gwidget->TensoChannTB_2, 3, 0, 1, 1);
	    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwidget->TensoChannTB_2),global->tenso_enabled_ch_2);
	    gtk_widget_show (gwidget->TensoChannTB_2);
	    g_signal_connect (GTK_CHECK_BUTTON(gwidget->TensoChannTB_2), "toggled", G_CALLBACK (TensoChannTB_2_changed), all_data);

      // 3
	    gwidget->TensoChannTB_3 = gtk_check_button_new_with_label (_(" 3"));
	    g_object_set_data (G_OBJECT (gwidget->TensoChannTB_3), "effect_info", GINT_TO_POINTER(CH_3));
	    gtk_widget_set_halign (gwidget->TensoChannTB_3, GTK_ALIGN_FILL);
	    gtk_widget_set_hexpand (gwidget->TensoChannTB_3, TRUE);
	    gtk_grid_attach(GTK_GRID(gwidget->table_TensoChannels), gwidget->TensoChannTB_3, 4, 0, 1, 1);
	    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gwidget->TensoChannTB_3),global->tenso_enabled_ch_3);

	    gtk_widget_show (gwidget->TensoChannTB_3);
	    g_signal_connect (GTK_CHECK_BUTTON(gwidget->TensoChannTB_3), "toggled", G_CALLBACK (TensoChannTB_3_changed), all_data);

}
