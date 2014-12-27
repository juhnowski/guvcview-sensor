/*******************************************************************************#
#           guvcview              http://guvcview.sourceforge.net               #
#                                                                               #
#           Ilya Juhnowski <juhnowski@gmail.com>                                 #
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
#include "meta.h"

int initMetaData(struct ALL_DATA *all_data)
{
	struct metaData *mdata = NULL;
	XIMU* xdata = NULL;
	ENCODER* edata = NULL;
	TENSO* tdata = NULL;
	XimuBuff* xbuff = NULL;
	XImuRecord* xrec = NULL;
	TensoBuff* tbuff = NULL;
	TensoRecord* trec = NULL;

	EncoderBuff* ebuff = NULL;
	EncoderRecord* erec = NULL;

	mdata = g_new0(struct metaData , 1);
	xdata = g_new0(XIMU , 1);
        edata = g_new0(ENCODER , 1);
	tdata = g_new0(TENSO , 1);
	xbuff = g_new0(XimuBuff , 1);

	xrec = g_new0(XImuRecord, 1);
    
	xbuff->frame = xrec;
	xdata->data = xbuff;
	
	trec = g_new0(TensoRecord, 1);
	tbuff = g_new0(TensoBuff, 1);
	tbuff->frame = trec;
	tdata->tbuff = tbuff;
	
	ebuff = g_new0(EncoderBuff, 1);
	erec = g_new0(EncoderRecord,1);
	ebuff->frame = erec;
	edata->ebuff = ebuff;
	
	mdata->edata = edata;
	mdata->tdata = tdata;
	mdata->xdata = xdata;

	all_data->mdata = mdata;
	
  return (0);
};

int freeMetaData(struct ALL_DATA *all_data)
{
  
  free_ximu_buff(all_data->mdata->xdata->data);
  g_free(all_data->mdata->xdata->data->frame);
  g_free(all_data->mdata->xdata->data);
  
  free_encoder_buff(all_data->mdata->edata->ebuff);
//  g_free(all_data->mdata->edata->path);
  g_free(all_data->mdata->edata->ebuff);
  g_free(all_data->mdata->edata);
  
  free_tenso_buff(all_data->mdata->tdata->tbuff);
  g_free(all_data->mdata->tdata->tbuff);
//  g_free(all_data->mdata->tdata->path);
  g_free(all_data->mdata->tdata);
  
  return (0);
};


int submit_tenso_buff(TensoBuff* buff)
{
  
  return (0);
}

int submit_encoder_buff(EncoderBuff *buff)
{
  return (0);
}

int submit_ximu_buff(XimuBuff* data)
{
  return (0);
}

int free_tenso_buff(TensoBuff* buff)
{
  TensoRecord *current;
  current = buff->frame;
  
  //find last record
  while (current->next != 0)
  {
      current = current->next;
  }
  
  //free allocated records
  while(current->prev !=0)
  {
    current = current->prev;
    g_free(current->next);
  }
 // g_free(current);
}

int free_encoder_buff(EncoderBuff *buff)
{
  EncoderRecord *current;
  current = buff->frame;
  
  //find last record
  while (current->next != 0)
  {
      current = current->next;
  }
  
  //free allocated records
  while(current->prev !=0)
  {
    current = current->prev;
    g_free(current->next);
  }
//  g_free(current);  
}

int free_ximu_buff(XimuBuff* buff)
{
  XImuRecord *current;
  current = buff->frame;
  
  //find last record
  while (current->next != 0)
  {
      current = current->next;
  }
  
  //free allocated records
  while(current->prev !=0)
  {
    current = current->prev;
    g_free(current->next);
  }
//  g_free(current);    
}