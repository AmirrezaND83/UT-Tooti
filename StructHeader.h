#include "WomenLifeFreedom.h"

typedef struct Post
{
    char* SenderID;
    char* PrimaryKey;
    int PostID;
    int Likes;
    char* Text;

    struct Post* Next;
} Post;

int GeneratePostNumber(Post* dummy);

int SendPost(Post* dummy, char *senderID, char *text);

int SendToLikedPosts(Post* dummy, char *senderID, int postid);

int DeletePost(Post *dummy, int postid);

int EditPost(Post *dummy, int postid, char *text);

void PrintPost(Post* post); 

char* GeneratePostPK(char* senderid, int postid);


typedef struct User
{
    char* Username;
    char* Password;
    Post* PostsDummy;

    Post* LikedPostsDummy;

    struct User* Next;
} User;


User* FindLastUser(User *first);

int SignUpUser(User* dummy, char* username, char* password);

void DeletePosts(User* user);

int DeleteAccount(User* dummy, char* username);

Post* FindPost(Post* dummy, int id, SearchFlag flag);

User* FindUser(User* dummy, char *username, SearchFlag flag);

int LikePost(User* dummy, char* senderId, int postId);

void PrintUser(User* user, UserPrintFlag flag);
