#include <stdio.h>
#include <string.h>
#include "agent.h"
#include <gtk/gtk.h>
enum
{
 ID,
 PASSWORD,
 NAME,
 ADRESS,
 PHONE,
 COLUMNS
};
/***********************************************************/
void ajouter_agent(Agent a)
{
  FILE *f;
  f=fopen("agent.txt","a+");
  if (f!=NULL)
{
  fprintf(f,"%s %s %s %s %s \n",a.id,a.password,a.name,a.adress,a.phone);
  fclose(f);
}
}
/***********************************************************/
void afficher_agent (GtkListItem * liste)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
       char id[30];
       char password[30];
       char name[30];
       char adress[30];
       char phone[30];
       store=NULL;
  
           FILE*f;
     store=gtk_tree_view_get_model(liste);
           if(store==NULL)
{
          renderer = gtk_cell_renderer_text_new();
          column = gtk_tree_view_column_new_with_attributes(" id",renderer,"text",ID, NULL);
          gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
          renderer = gtk_cell_renderer_text_new();
          column = gtk_tree_view_column_new_with_attributes(" password",renderer,"text",PASSWORD, NULL);
          gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
          renderer = gtk_cell_renderer_text_new();
          column = gtk_tree_view_column_new_with_attributes(" name",renderer,"text",NAME, NULL);
          gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
          renderer = gtk_cell_renderer_text_new();
          column = gtk_tree_view_column_new_with_attributes(" adress",renderer,"text",ADRESS, NULL);
          gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
           renderer = gtk_cell_renderer_text_new();
          column = gtk_tree_view_column_new_with_attributes(" phone",renderer,"text",PHONE, NULL);
          gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
      store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
      f= fopen("agent.txt","r");
      if(f==NULL)
        {
                return;
        }
     else 
       {
          f= fopen("agent.txt","a+");
                    while(fscanf(f,"%s %s %s %s %s \n",id,password,name,adress,phone)!=EOF)
            {
     gtk_list_store_append (store, &iter);
     gtk_list_store_set (store, &iter, ID, id, PASSWORD, password, NAME, name, ADRESS, adress, PHONE, phone, -1); 
            }
              fclose(f);
       gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
       g_object_unref (store);
       }
}
}

/*************************suuprimer*************************************/
void supprimer_agent(char ids[20])
{Agent a;
FILE* f=NULL;
FILE* Ftemp;
f=fopen("agent.txt","r");
Ftemp=fopen("agenttemp.txt","w");
fclose(Ftemp);
Ftemp=fopen("agenttemp.txt","a+");
if (f!=NULL)
while(fscanf(f,"%s %s %s %s %s\n",a.id,a.password,a.name,a.adress,a.phone)!=EOF)
{
     fscanf(f,"%s %s %s %s %s\n",a.id,a.password,a.name,a.adress,a.phone);

     if(strcmp(a.id,ids)!=0)
         {
		fprintf(Ftemp,"%s %s %s %s %s \n",a.id,a.password,a.name,a.adress,a.phone);
   	 }
}

fclose(f);
fclose(Ftemp);
remove("agent.txt");
rename("agenttemp.txt","agent.txt");
}
/******************************modifier********************/
void modifier_agent(char idm)
{
  FILE*f;
  FILE*Ftemp;
  Agent a;

  f=fopen("agent.txt","r");
  Ftemp=fopen("agent.tmp","w");
  if(f!=NULL)
  {
    while(fscanf(f,"%s %s %s %s %s \n",a.id,a.password,a.name,a.adress,a.phone)!=EOF)
    {
      if(a.id != idm)
      {	fprintf(Ftemp,"%s %s %s %s %s \n",a.id,a.password,a.name,a.adress,a.phone);}
    else{
            fprintf(Ftemp,"%s %s %s %s %s \n",a.id,a.password,a.name,a.adress,a.phone);}
    }
  fclose(f);
  fclose(Ftemp);

  remove("agent.txt");
  rename("agent.tmp","agent.txt");
}
}
