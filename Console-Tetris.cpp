#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<time.h>
#include<fstream>

// Gloal Values
int stage[21][12] = {0};
int block[4][4] = {{0,0,0,0},
                   {0,1,1,0},
                   {0,1,1,0},
                   {0,0,0,0}};
int field[21][12] = {0};
int y; // y ���W
int x = 4; // x ���W
int gameover; //1 �ŃQ�[���I�[�o�[
int oneline,twoline,threeline,fourline;


int NANIDO_NUM=20000; //default level


/* block data */
int block_list[7][4][4] = {{{0,1,0,0},
{0,1,0,0},
{0,1,0,0},
{0,1,0,0}},
{{0,0,0,0},
{0,1,1,0},
{0,1,0,0},
{0,1,0,0}},
{{0,0,1,0},
{0,1,1,0},
{0,1,0,0},
{0,0,0,0}},
{{0,1,0,0},
{0,1,1,0},
{0,0,1,0},
{0,0,0,0}},
{{0,0,0,0},
{0,1,0,0},
{1,1,1,0},
{0,0,0,0}},
{{0,0,0,0},
{0,1,1,0},
{0,1,1,0},
{0,0,0,0}},
{{0,0,0,0},
{0,1,1,0},
{0,0,1,0},
{0,0,1,0}}};

/*			*/
int MENU(); //���j���[
void level_change(); //���x���ύX
int game_over(); //�Q�[���I�[�o�[�`��
void Title(); //�^�C�g���`��
void Start_game(); //�Q�[���X�^�[�g����
int about_game(); //Readme ��݂���
void disp_Field(); // �t�B�[���h�`��
bool makeBlocks(); //�u���b�N�`��
void first_clean(); //������
void MoveBlock(int, int); //�u���b�N�ړ�����
void block_on(); // �u���b�N�Œ菈��
bool check_over(int, int); //�u���b�N�ړ��͈͊m�F����
void type_control_Blocks(); //�L�[���͏���
bool turn_block(); //�u���b�N��]����
void check_line(); //���̗�̊m�F����
void delete_blocks(); //�`�ʂ̂��Ȃ�������
// void Ranking();

/*
*
*
* MAIN
************************/
int main()
{
 int which_menu=MENU();
 
 switch(which_menu){
	case 1:
		Start_game();
		break;
	case 2:
		level_change();
		main();
		break;
	case 3:
		about_game();
		main();
		break;
	case 4:
		return 0;
	case 0:
		std::cerr<<"Choose 1�`4"<<std::endl;
		return -1;
 }
 return 0;
}
/*
*
*
*game_over(): �Q�[���I�[�o�[aa��`��
******************************************/
int game_over()
{
 using namespace std;
 
 char a;
 cout << " #####     #    #     # ####### ####### #     # ####### ######"<<endl;
 cout << "#     #   # #   ##   ## #       #     # #     # #       #     #"<<endl;
 cout << "#        #   #  # # # # #       #     # #     # #       #     #"<<endl;
 cout << "#  #### #     # #  #  # #####   #     # #     # #####   ######"<<endl;
 cout << "#     # ####### #     # #       #     #  #   #  #       #   #"<<endl;
 cout << "#     # #     # #     # #       #     #   # #   #       #    #"<<endl;
 cout << " #####  #     # #     # ####### #######    #    ####### #     #"<<endl;
 cout << "\n\nPress any key and Enter"<<endl;
 cin >> setw(1) >> a;
 
 return 0;
}

/*
*
*
*about_game() : Readme����ǂݎ��
****************************************/
int about_game()
{
 char readok;
 char ch;
 std::ifstream ifs("readme.txt");
 if(!ifs){std::cerr << "����ERROR" << std::endl;return -1;}
 while((ch=ifs.get())!=EOF){
	std::cout<<ch;
 }
 
 std::cout<< "\n\n<�ǂݏI���܂�����0����͂��Ă�������>"<<std::endl;
 std::cin >> std::setw(1) >> readok;
 return 0;
}

/*
*
*
*level_change(): ���x���ύX
*************************************/
void level_change()
{
 int n=1;
 int ch_level;
 int ch_num;
 char ans;
 std::cout<<"\t<LEVEL CHANGE>"<<std::endl;
 std::cout<<"Default level is Normal"<<std::endl;
 std::cout<<"1: Easy 2: Normal 3: Hard 4: Very Hard 5: Altimate"<<std::endl;
 std::cout<< ">> ";
 std::cin>>std::setw(1)>>ch_level;
	switch(ch_level){
		case 1:
			ch_num=27000;
			break;
		case 2:
			ch_num=20000;
			break;
		case 3:
			ch_num=10000;
			break;
		case 4:
			ch_num=5000;
			break;
		case 5:
			ch_num=500;
			break;
	}
	
 do{
	std::cout<<"Change Level. OK ?"<<std::endl;
	std::cout<<" (y/n)>> "<<std::flush;
	std::cin>>std::setw(1)>>ans;
	if(ans=='y'){
		NANIDO_NUM=ch_num;
		n=0;
	}
	if(ans=='n'){
		n=0;
	}
 }while(n);
}		

/*
*
*Start_game() : �Q�[���J�n
***********************************/
void Start_game()
{
int time = 0; 
first_clean(); 

 while(!gameover) { //�Q�[�����ް�܂ŉi�����[�v
        if(kbhit()) {
                type_control_Blocks();
        }
        if(time<NANIDO_NUM){
                time++;
        }else{
            delete_blocks();    
			time = 0;
        }
 }

}

/*
*
*
*MENU(): ���j��-
********************************/
int MENU()
{
 Title();
 int select_num=0;
 
 std::cin>>std::setw(1)>>select_num;
 switch(select_num){
	case 1:
	case 2:
	case 3:
	case 4:
		break;
	default:
		select_num=0;
		break;
  }
  return select_num;
 }
 
/*
*
*
*Title(): �^�C�g��
****************************/
void Title()
{
 using namespace std;
 
 system("cls");
 
 cout<<"#==============================================================================#"<<endl;
 
 cout<<"####### ####### ####### ######    ###    #####"<<endl;
 cout<<"   #    #          #    #     #    #    #     #"<<endl;
 cout<<"   #    #          #    #     #    #    #"<<endl;
 cout<<"   #    #####      #    ######     #     #####"<<endl;
 cout<<"   #    #          #    #   #      #          #"<<endl;
 cout<<"   #    #          #    #    #     #    #     #"<<endl;
 cout<<"   #    #######    #    #     #   ###    #####\t\tmade by falgon"<<endl;
 cout<<"\n\n\n"<<endl;
 
 cout<<"\t<Menu>"<<endl;
  cout<<"\t1: Start Game\t2: Level Change\t3: About this GAME\t4: Quit"<<endl;
 
 cout<<"#==============================================================================#"<<endl;
 cout<<"Choose >> ";
 }
 
 

/*
*
*
*disp_Field(): ��ʕ\��
***************************/
void disp_Field()
{
 system("cls");

 for(int i=0; i<21; i++) {
        for(int j=0; j<12; j++) {
                switch(field[i][j]) {
                        case 0:
                                std::cout<<"�@"<<std::flush;
                                break;
                        case 9:
                                std::cout<<"��"<<std::flush;
                                break;
                        default:
                                std::cout<<"��"<<std::flush;
                                break;
                }
        }
 std::cout<<std::endl;
 }
 std::cout<<"\n"<<"��s���� : "<<oneline<<" ��s���� : "<<twoline<<" �O�s���� : "<<threeline<<" �l�s���� :"<<fourline<<std::flush;
 std::cout <<"\n\t�� A\tS ��\tD �� ��][Space]";
 if(gameover){
        system("cls");
		game_over();
 }
}

/*
*
*
*first_clean(): ������
************************/
void first_clean()
{
for(int i=0;i<=20;i++) {
        for(int j=0;j<=11;j++) {
                if((j==0) || (j==11) || (i==20)) {
                        field[i][j] = stage[i][j] = 9;
                }else{
                        field[i][j] = stage[i][j] = 0;
                }
        }
}
makeBlocks();
disp_Field();
}

/*
*
*
*make_Blocks(): �u���b�N�쐬����
**************************/
bool makeBlocks()
{
 int i,j;
 int block_type;
  
 x = 4;
 y = 0;
 
 srand((unsigned)time(NULL));
 block_type=rand()%7;
 
 for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		block[i][j]=0;
		block[i][j]=block_list[block_type][i][j];
	}
 }
  
 for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
                field[i][j+4] = stage[i][j+4] + block[i][j];
                if(field[i][j+4] > 1) {
                        gameover = 1;
                        return true;
                }
        }
}
return false;
}


/*
*
*
*MoveBlock(): �u���b�N��`��
***************************/
void MoveBlock(int x2, int y2)
{
 int i, j; 
 //�u���b�N���폜
 for(i = 0; i<4; i++) {
        for(j = 0; j<4; j++) {
                field[y+i][x+j] -= block[i][j];
        }
 }
//���W���X�V
 x=x2;
 y=y2;
//�X�V���ꂽ�l�Ńu���b�N�l����
 for(i = 0; i<4; i++) {
        for(j = 0; j<4; j++) {
                field[y+i][x+j] += block[i][j];
        }
 }
 disp_Field();
}

/*
*
*
*block_on(): �����̃u���b�N���Œ肷��
******************************/
void block_on()
{
 int i,j;
 for(i = 0; i<21; i++) {
        for(j = 0; j<12; j++) {
                stage[i][j] = field[i][j];
        }
 }
 check_line();
 for(i=0; i<21; i++){
	for(j=0; j<12; j++){
		field[i][j]=stage[i][j];
	}
 }
}

/*
*
*
*check_over(): �u���b�N�̗L�����m�F
*****************************/
bool check_over(int x2, int y2)
{
 for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
                if(block[i][j]) {
                        if(stage[y2 + i][x2 + j] != 0) {
                                return true;
                        }
                }
        }
}
return false;
}
/*
*
*
*type_control_blocks(): �L�[���́A���쏈��
******************************/
void type_control_Blocks()
{
  char key;
  key=getch();
  switch(key){
        case 'd': 
                if(!check_over(x+1,y)){
                        MoveBlock(x+1,y);
                }
                break;
        case 'a': 
                if(!check_over(x-1,y)){
                        MoveBlock(x-1,y);
                }
                break;
        case 's':
                if(!check_over(x,y+1)){
                        MoveBlock(x,y+1);
                }
                break;
        case ' ':
                turn_block();
 }
}

/*
*
*
*turn_block(): ��]����
*********************************/
bool turn_block()
{
 int i,j;
 int tmp[4][4]={0};
 
 for(i=0; i<4; i++){ //�u���b�N���ꎞ�ۑ�
        for(j=0; j<4; j++){
                tmp[i][j]=block[i][j];
        }
 }
 
 for(i=0; i<4; i++){ //��]
        for(j=0; j<4; j++){
                block[i][j]=tmp[3-j][i];
        }
 }
 if(check_over(x,y)){ // �d�Ȃ�Ɖ�]�ł��Ȃ��̂Œ��~������
        for(i=0; i<4; i++){
                for(j=0; j<4; j++){
                        block[i][j]=tmp[i][j];
                }
        }
 return true;
 }
 
 for(i=0; i<4; i++){
        for(j=0; j<4; j++){
                field[y+i][x+j]-=tmp[i][j];
                field[y+i][x+j]+=block[i][j];
        }
 }
 disp_Field();
 return false;
}

/*
*
*
*check_line(): �����̌���
*********************************/
void check_line()
{
 int i,j,k;
 int comp;
 int lines=0;
 
  while(1){
	for(i=0; i<20; i++){
		comp=1;
		for(j=1;j<11;j++){
			if(stage[i][j]==0){
				comp=0;
			}
		}
		if(comp==1)break;
	}
	if(comp==0)break;
	
	lines++;
	
	for(j=1;j<11;j++){
		stage[i][j]=0;
	}
	
	for(k=i;k>0;k--){
		for(j=1;j<11;j++){
			stage[k][j]=stage[k-1][j];
		}
	}
 }
 switch(lines){
	case 1:
		oneline++;
		break;
	case 2:
		twoline++;
		break;
	case 3:
		threeline++;
		break;
	case 4:
		fourline++;
		break;
	default:
		break;
  }
 }

void delete_blocks()
{
 if(!check_over(x,y+1)){
	MoveBlock(x,y+1);
 }else{
	block_on();
    makeBlocks();
    disp_Field();
 }
}

