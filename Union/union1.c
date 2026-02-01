union Studnet
{
    int roll;
    char name;
    float marks;
};

void main()
{
 
    union Studnet s1;
    s1.name='o';
    s1.roll=8;
    
    s1.marks = 98;
    printf("%.2f",s1.marks);

}
