#include "common.h"
#include "hash_table.h"
#include "list_linked.h"
#include "stdio.h"
#include "hash_table.h"
#include "list_linked.h"
#include "utils.h"
#include "webstore.h"
#include "merch.h"
#include "cart2.h"
#include "ui.h"


int main(int argc, char *argv[]) {

  webstore_t *store = store_create();



  char str[128] = "      ";
  char str2[128] = "      ";
  char str3[128] = "      ";
  char *b = NULL;

  b = ask_question_string("enter name: ");
  strcpy(str, b);
  free(b);
  b = ask_question_string("enter desc: ");
  strcpy(str2, b);
  free(b);
  b =  ask_question_string("enter shelf: ");
  strcpy(str3,b);
  free(b);
  int price = ask_question_int("enter price: ");
  
  int amount = ask_question_int("enter amount: ");

  NEW_ITEM(store, str, str2, 100);
  NEW_ITEM(store, "Orange",   "Imported fruit from Italy.", 15);
  NEW_ITEM(store, "Coconut",  "Edible tropical fruit from Congo.", 30);
  NEW_ITEM(store, "Mandarin", "Not GMO-free.", 5);
  NEW_ITEM(store, "Mountain Bike", "Prefessional competition bike.", 1000);
  NEW_ITEM(store, "LADA (Car)",    "Soviet import, manifactured by AvtoVAZ", 4000);
  NEW_ITEM(store, "Electric Bike", "AAA batteries not included.", 800);
  NEW_ITEM(store, "Skateboard",    "Small Longboard.", 40);
  NEW_ITEM(store, "Fake Rolex Watch", "A Fake Golden Rolex Watch", 100);
  NEW_ITEM(store, "Adidas Pants",     "the Classic Adidas Pants", 200);
  NEW_ITEM(store, "Used Jacket",      "From the hermes 1999 Summer Collection", 8000);
  NEW_ITEM(store, "Sandals",          "Simple sandals.", 120);

  SET_ITEM_LOC(store, str, str3, 109);		      
  SET_ITEM_LOC(store, "Apple",    "F12", 128);		      
  SET_ITEM_LOC(store, "Orange",   "F12", 64);
  SET_ITEM_LOC(store, "Mandarin", "F12", 16);
  SET_ITEM_LOC(store, "Coconut",  "F12", 16);
  SET_ITEM_LOC(store, "Mountain Bike", "M01", 28); 
  SET_ITEM_LOC(store, "LADA (Car)",    "M01", 4);
  SET_ITEM_LOC(store, "Electric Bike", "M01", 10);
  SET_ITEM_LOC(store, "Skateboard",    "M02", 160);
  SET_ITEM_LOC(store, "Fake Rolex Watch", "C00", 18); 
  SET_ITEM_LOC(store, "Adidas Pants",     "C01", 6);
  SET_ITEM_LOC(store, "Used Jacket",      "C99", 1);
  SET_ITEM_LOC(store, "Sandals",          "C00", 36);

  show_stock(store);

  store_destroy(store);
  return 0;
}

