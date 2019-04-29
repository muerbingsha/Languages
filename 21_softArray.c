#include <stdio.h>
#include <stdlib.h>

typedef struct _Player {
    int id;
    char *name;
}Player;

typedef struct _Arena{
    int len;        //4
    Player* array[]; //0
}Arena;

int main()
{
    int len = 10;
    printf("The struct's size is %lu\n",sizeof(Arena));  //4
    
    Arena *go = (Arena *)malloc(sizeof(Arena) + sizeof(Player) * len); //8
    printf("go's size is %lu \n", sizeof(go));
    
    go->len = len;
    for (int i = 0; i < go->len; i++){
        Player *p = (Player *)malloc(sizeof(Player));
        p->id = i;
        
        
        if (i == 0){
            p->name = "Mary";
        } else if (i == 1){
            p->name = "John";
        } else if (i == 2){
            p->name = "Peter";
        } else if (i == 3){
            p->name = "Henry";
        } else if (i == 4){
            p->name = "ZhangSan";
        } else if (i == 5){
            p->name = "LiSi";
        } else if (i == 6){
            p->name = "Wanger";
        } else if (i == 7){
            p->name = "Sheldon";
        } else if (i == 8){
            p->name = "Hemmiton";
        } else if (i == 9){
            p->name = "Mashmallow";
        }
        
        go->array[i] = p;
    }
 
    
    
    //print
    for(int i = 0; i < go->len; i++){
        printf("[player] id: %d, name: %s is on \n", go->array[i]->id, go->array[i]->name);
    }
    
    printf("go's size is %lu \n", sizeof(go)); //8
}
