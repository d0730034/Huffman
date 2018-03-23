#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node
{
    char num;//0 mean null branch node, others mean leaves
    struct node *left;
    struct node *right;
} ;

struct CompressionNode //the data structure you were using during your compression algorithm
{
    char num;//means the A in A=001
    char string[9];//the 001
    struct CompressionNode *next;
} ;
void ChangeTB(char * stre,char * result,struct CompressionNode *head1);//txt to binary
void CreatComNode(char * CodeFile,struct CompressionNode *head);//create the compression node to store the base info
void addnode(struct node *head,char ch,char *str);// add node to the tree
void WriteToBianary(char * CodeFile,char *string);//write the string into file
void ReadTxt(char * CodeFile,char *string);//read the txt
void ReadBianary(char * CodeFile,char *string);//read the binary
void ChangeBT(char * stree,char * result,struct node *head);// binary to txt
void WriteToTxt(char * CodeFile,char *string);//wirte to txt
void deleteTree(struct node *head){
    //TODO: Write a function that deletes(frees) the data structure
        //used during the decompression algorithm
    struct node *q=head;
    if(q->left!=NULL)
    {	
        deleteTree(q->left);
    }
    if(q->right!=NULL)
    {	
        deleteTree(q->right);
    }
    free(q);
}

void deleteList(struct CompressionNode *headDataCom){
    //TODO: Write a function that deletes(frees) the data
        //structure you were using during your compression algorithm
        struct CompressionNode *p=headDataCom;
        while(p!=NULL)
        {
            struct CompressionNode *q=p;
            p=p->next;
            free(q);
        }
}

/*	Parse the command inputs:
*
*	argv[0] is always program name
*	-c or -d:			will determine whether to compress or decompress: -c or -d 
*	<PATHTOSOURCE>:		will determine what file to compress(or decompress)(Error if it is a folder)
*	--code:				is a flag to say that the next argument is the file with the huffman codes
*	<PATHTOCODE>:		is the path to the huffman codes file
*	-p:(optional) 		to specify a destination file.
*	<PATHTODEST>:		(if -p is there) specifies the filename to compress(decompress) to.
*		Default destination path(no -p flag) is out.huf and out.dec for compress and decompress, respectively
*		if invalid path, error and exit.
*
*  NOTE:  ARGUMENTS CAN BE IN ANY ORDER, AS LONG AS EACH PATH
            IS PRECEDED BY ITS RESPECTIVE FLAG
*    This means that it could be:
*		./huffman --code <PATHTOCODE> -c <PATHTOSOURCE>    or
*		./huffman -d <PATHTOSOURCE> -p <PATHTODEST> --code <PATHTOCODE>    or
*		./huffman -p <PATHTODEST> -d <PATHTOSOURCE> --code <PATHTOCODE>
* 
*		etc..............
*
*	valid syntax shorthand:
*	./huffman <-c|-d> <PATHTOSOURCE> --code <PATHTOCODE> [-p <PATHTODEST>]
*/

int main(int argc,char*argv[])
{
    char comType;
    char *PATHTOSOURCE;
    char *PATHTOCODE;
    char *PATHTODEST;
    char result[2000];//the result which write to the file in the compression algorithm
    char resultBT[3000];// the result in the decompression algorithm
    char stre[2000];//store the data read from the file
    int i = 0;
    struct CompressionNode *headDataCom=(struct CompressionNode *)malloc(sizeof(struct CompressionNode));//build the data structure you were using during your compression algorithm
    if (argc != 5 && argc != 7)
    {
        printf("The number of arguments is not valid!\n");
        return -1;
    }

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "-d"))
        {
            comType = argv[i][1];
            i++;
            PATHTOSOURCE = argv[i];
        }
        if (!strcmp(argv[i], "--code"))
        {
            i++;
            PATHTOCODE = argv[i];
        }
        if (!strcmp(argv[i], "-p"))
        {
            i++;
            PATHTODEST = argv[i];
        }
    }

    CreatComNode(PATHTOCODE,headDataCom);
    
    //head1=head1->next;
    if(comType =='c')//compress -c
    {
        ReadTxt(PATHTOSOURCE,stre);
    
        //printf("%s\n",stre);
        ChangeTB(stre,result,headDataCom);//txt to binary
        
        //printf("%s\n",result);
        //printf("%d",result[0]);
        if(argc==7)//judge the PATHTODEST is empty
        {
            WriteToBianary(PATHTODEST,result);//not empty
        }
        else
        {
            WriteToBianary("out.huf",result);//empty
        }
    }
    else if(comType =='d')//decompress: -d
    {
        struct CompressionNode *q;
        struct node *head=(struct node *)malloc(sizeof(struct node));//creat the tree
        head->left=NULL;
        head->right=NULL;
        head->num='0';
        q=headDataCom->next;
        //printf("num %c,%c,%c,%c\n",q->num,q->string[0],q->string[1],q->string[2]);
        while(q!=NULL)
        {
            addnode(head,q->num,q->string);
            q=q->next;
        }
        ReadBianary(PATHTOSOURCE,stre);
        ChangeBT(stre,resultBT,head);// binary to txt
        if(argc==7)
        {
            WriteToTxt(PATHTODEST,resultBT);
        }
        else
        {
            WriteToTxt("out.dec",resultBT);
        }
        deleteTree(head);
    }
    else
    {
        return -1;
    }
    deleteList(headDataCom);
    return 1;
}

void addnode(struct node *head,char ch,char *str)
{
    int i=0;
    struct node *p=head;
    //printf("num %c,%c,%c,%c\n",ch,str[0],str[1],str[2]);
    while(str[i]!='\0')//judeg the input weather null
    {
        //printf("str[i] %c",str[i]);
        if(str[i]=='0')//add left
        {
            if(p->left==NULL)
            {
                struct node *q=(struct node *)malloc(sizeof(struct node));
                q->left=NULL;
                q->right=NULL;
                q->num='0';
                p->left=q;
            }
            p=p->left;
        }
        else//add right
        {
            if(p->right==NULL)
            {
                struct node *q=(struct node *)malloc(sizeof(struct node));
                q->left=NULL;
                q->right=NULL;
                q->num='0';
                p->right=q;
            }
            p=p->right;
        }
        i++;
        //printf("%d",i);
    }
    p->num=ch;
    //printf("%c",p->num);
}

void CreatComNode(char * CodeFile,struct CompressionNode *head)
{
    FILE *fpCode;	
    char buf[200];
    struct CompressionNode *q=head;
    fpCode=fopen(CodeFile,"r");
    if(!fpCode)
    {
        printf("can't open file\n");
        return ;
    }

    while(fgets(buf, 200, fpCode)!=0)//read a line
    {
        struct CompressionNode *temp=(struct CompressionNode *)malloc(sizeof(struct CompressionNode));//new a node
        int i=0;
        for(i=0;buf[i]!='\0';i++)
        {
            if(buf[i+1]=='=')//judeg the char weather =,A=001
            {
                int m=0;
                temp->num=buf[i];
                i=i+2;
                while(buf[i]!='\0'&&buf[i]!='\n')
                {
                    temp->string[m]=buf[i];
                    //printf("%c\n",temp->string[m]);
                    m++;
                    i++;
                }
                temp->string[m]='\0';
                temp->next=NULL;
                q->next=temp;
                
                q=q->next;
                break;
            }
        }
    }
    fclose(fpCode);
}

void WriteToBianary(char * CodeFile,char *string)
{
    FILE *fpCode;
    int j;
    fpCode=fopen(CodeFile,"wb");
    if(!fpCode)
    {
        printf("can't open file\n");
        return ;
    }
    for(j=0;string[j]!='\0';j++)
    {
        fwrite(& string[j], sizeof( unsigned char ), 1, fpCode );
    }
    fclose(fpCode);
}

void ReadTxt(char * CodeFile,char *str)
{
    FILE *fpCode;
    int j;
    char ch;
    fpCode=fopen(CodeFile,"r");
    if(!fpCode)
    {
        printf("can't open file\n");
        return ;
    }
    j=0;
    ch = fgetc(fpCode);
    str[j++]=ch;
    while (ch != EOF)
    {        
      ch = fgetc(fpCode);
      if(ch==EOF)
        break;
      str[j++]=ch;
    }   
    str[j]='\0';
    fclose(fpCode);
}

void ChangeTB(char * stre,char * result,struct CompressionNode *head1)//txt to binary
{
    int k,i,j;
    char stree[5000];
    k=0;
    i=0;
    for(j=0;stre[j]!='\0';j++)//store the example 011 in string
    {
        int n=0;
        struct CompressionNode *q=head1->next;
        while(stre[j]!=q->num)
        {
            q=q->next;		
        }	   
        while(q->string[n]!='\0')
        {
            stree[i]=q->string[n];
            //printf("string %c\n",q->string[n]);
            i++;
            n++;
            k++;
        }	
    //	i=i-1;
    }
    
    stree[i]='\0';
    printf("%d",i);
    i=0;
    k=0;
    for(j=0;stree[j]!='\0';j++)//change string to huffman
    {
        if(i==0)
        {
            result[k]=0;
            result[k]=result[k]|((stree[j]-'0')<<(7-i));
            i++;
        }
        else if(i<8)
        {
            result[k]=result[k]|((stree[j]-'0')<<(7-i));
            i++;
        }
        else
        {
            i=0;
            k=k+1;
            result[k]=0;
            result[k]=result[k]|((stree[j]-'0')<<(7-i));
            i++;
        }
        //printf("j%d",j);
    }
    result[k+1]='\0';
}

void ReadBianary(char * CodeFile,char *str)
{
    FILE *fpCode;
    int j;
    char ch;
    fpCode=fopen(CodeFile,"rb");
    if(!fpCode)
    {
        printf("can't open file\n");
        return ;
    }
    j=0;
    ch = fgetc(fpCode);
    str[j++]=ch;
    while (!feof(fpCode))
    {        
      ch = fgetc(fpCode);
     /* if(ch==EOF)
        break;*/
      str[j++]=ch;
    } 
    str[j-1]='\0';
    //printf("B%s",string);
    fclose(fpCode);
}

void ChangeBT(char * stree,char * result,struct node *head)// binary to txt
{
    struct node *q=head;

    int i,qq;//qq record the position of  result
    qq=0;
    for(i=0;stree[i]!='\0';i++)//take a number of  bits
    {
        int m;
        //printf("BT=%d",i);
        for(m=7;m>=0;m--)
        {
            int k=(stree[i]>>m)&0x01;//take a bit
            if(k==0)//go to left
            {
                if(q->left!=NULL)
                    q=q->left;
                else
                {
                   // printf("11");
                    result[qq]='\0';
                    return ;//wrong position
                }
            }
            else//go to right
            {
                if(q->right!=NULL)
                    q=q->right;
                else
                {
                  //  printf("22");
                    result[qq]='\0';
                    return ;//wrong position
                }
            }
            if(q->num!='0')
            {
                result[qq]=q->num;
                //printf("%c",result[qq]);
                qq++;
                q=head;

            }
        }
    }
    result[qq]='\0';
}

void WriteToTxt(char * CodeFile,char *string)
{
    FILE *fpCode;
    int j;
    fpCode=fopen(CodeFile,"w");
    if(!fpCode)
    {
        printf("can't open file\n");
        return ;
    }
    for(j=0;string[j]!='\0';j++)
    {
        fwrite( &string[j], sizeof( unsigned char ), 1, fpCode );
    }
    fclose(fpCode);
}
