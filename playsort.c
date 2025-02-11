#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
        char title[100];
    char artist[100];
    char album[100];
    int release_date;
}Song;


void merge(Song *arr, int lb, int mid, int ub, char *attribute){
    int i,j,k;
    int n1= mid -lb+1;
    int n2=ub-mid;

    Song l[n1],r[n2];

    for(int i = 0; i < n1;i++){
        l[i]= arr[lb+i];
    }
    for(int j = 0; j < n2;j++){
        r[j]=arr[mid+1+j];
    }
    
    i = 0;
    j = 0;
    k=lb;
    while(i<n1 && j<n2){
        int compare;
        if(strcmp(attribute,"title")==0){
            compare = strcmp(l[i].title,r[j].title);
        }
        else if(strcmp(attribute,"artist")==0){
            compare = strcmp(l[i].artist,r[j].artist);
        }
        else if(strcmp(attribute,"album")==0){
            compare = strcmp(l[i].album,r[j].album);
        }
        else if(strcmp(attribute,"release_date")==0){
            compare = l[i].release_date-r[j].release_date;
        }

        if(compare <= 0){
            arr[k]=l[i];
            i++;
        }

        else{
            arr[k] = r[j];
            j++;
        }

        k++;
    }

    if(i>=n1){
        while(j<n2){
            arr[k] = r[j];
            j++;
            k++;
        }
    }

    else if( j>= n2){
        while(i < n1){
            arr[k] = l[i];
            i++;
            k++;
        }
    }

}


void merge_sort(Song *arr, int lb, int ub, char *attribute){
    if(lb<ub){
        int mid = (lb+ub)/2;
        merge_sort(arr,lb,mid,attribute);
        merge_sort(arr,mid+1,ub,attribute);
        merge(arr,lb,mid,ub,attribute);
    }
}

void print_vals(Song *playlist, int size){
    printf("\nSorted playlist:\n");
    for(int i=0;i<size;i++){
        printf("%s by %s from %s released on %d\n", playlist[i].title, playlist[i].artist,playlist[i].album,playlist[i].release_date);
    }
}

int main(){
    int num_songs;
    printf("Enter the number of songs: ");
    scanf("%d",&num_songs);

    Song *playlist = (Song *)malloc(num_songs * sizeof(Song));

    for(int i=0;i<num_songs;i++){
        printf("Enter the details of the song number: %d \n",i+1);
        printf("Title: ");
        scanf(" %[^\n]s",playlist[i].title);
        printf("Artist: ");
        scanf(" %[^\n]s",playlist[i].artist);
        printf("Album: ");
        scanf(" %[^\n]s",playlist[i].album);
        printf("Release Date: ");
        scanf("%d",&playlist[i].release_date);
    }

    char attribute[20];
    int keepsort = 1;
    while(keepsort == 1){
        printf("\nEnter how you would like to sort your playlist by: \n1.Title \n2.Artist \n3.Album \n4.Release Date or \n5.EXIT\nWhats your choice: ");
        scanf(" %[^\n]s", attribute);

        if(strcmp(attribute,"exit")==0){
            keepsort = 0;
        }

        merge_sort(playlist, 0, num_songs-1,attribute);
        print_vals(playlist,num_songs);
    }

    free(playlist);
}
