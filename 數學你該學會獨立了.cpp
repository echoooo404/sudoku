#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


int solution[9][9];
bool row_used[9][10];//[��][�Ʀr]
bool col_used[9][10];
bool block_used[9][10];

int board[9][9];
bool editable[9][9];
bool has_error[9][9]={{false},{false}};
bool complete[9][9]={{false},{false}};

int cur_r = 0, cur_c = 0;//���Ц�m 

// ���m�ѽL�M�ϥΪ��A
void reset_board() {
    for (int i = 0; i < 9; i++) {
        for (int j = 1; j <= 9; j++) {
            row_used[i][j] = false;
            col_used[i][j] = false;
            block_used[i][j] = false;
        }
        for (int j = 0; j < 9; j++) {
            solution[i][j] = 0;
        }
    }
}

// �ˬd�Ʀr�O�_�i�H��b���w��m
bool can_use(int row, int col, int num) {
    int block_flag = (row / 3) * 3 + (col / 3);//�s���j�� 
    return !row_used[row][num] &&
           !col_used[col][num] &&
           !block_used[block_flag][num];
}

// �O���Ʀr�ϥΪ��A
void mark_used(int row, int col, int num, bool is_used) {
    int block_flag = (row / 3) * 3 + (col / 3);
    row_used[row][num] = is_used;
    col_used[col][num] = is_used;
    block_used[block_flag][num] = is_used;
}

// �H���ƦC1-9���Ʀr
void shuffle_numbers(int numbers[]) {
    for (int i = 0; i < 9; i++) {
        numbers[i] = i + 1;
    }
    random_shuffle(numbers, numbers + 9); // �H�����üƦr
}

// �ѼƿW�����j���
bool solve(int row, int col) {
    if (row == 9) return true;
    if (col == 9) return solve(row + 1, 0);
    if (solution[row][col] != 0) return solve(row, col + 1);

    int numbers[9];
    shuffle_numbers(numbers); // �H���ƦC�Ʀr

    for (int i = 0; i < 9; i++) {
        int num = numbers[i];
        if (can_use(row, col, num)) {
            solution[row][col] = num;
            mark_used(row, col, num, true);

            if (solve(row, col + 1)) return true;

            solution[row][col] = 0;
            mark_used(row, col, num, false);
        }
    }
    return false;
}

// �ͦ��ƿW�C��
void generate_sudoku() {
    srand(time(NULL));
    reset_board();

    // �ͦ������
    solve(0, 0);

    // �ƻs��
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = solution[i][j];
        }
    }

    // �����Ʀr�H�ͦ��D��
    int removed = 0;
    while (removed < 40) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            removed++;
        }
    }
}

// �C�L�ѵ� 
void print_solution(int b[9][9]) {
	cout<<endl<< "solution:" <<endl;
	
    for (int i = 0; i < 9; ++i)
    {
        
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            cout<< " " << b[i][j] << " ";
           
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }

}




 
//�ˬd��C��l�O�_�w�����Φ����~ 
int check_horizontal(int r,int c){
	
		int number[10]={0};
    int unseen=0,error=0;
    
    for(int b=0;b<9;b++){
    	
    	if(board[r][b]==0){unseen=1;continue;}
    	if(number[board[r][b]]){error=1;break;}
    	number[board[r][b]]++;
	
	}
	
	if(error)return 1;
    else if(unseen)return 0;
	else return 2;
	
}

//�ˬd�����l�O�_�w�����Φ����~ 
int check_vertical(int r,int c){

	
	int number[10]={0};
    int unseen=0,error=0;
    
    for(int b=0;b<9;b++){
    	
    	if(board[b][c]==0){unseen=1;continue;}
    	if(number[board[b][c]]){error=1;break;}
    	number[board[b][c]]++;
	
	}
	
	if(error)return 1;
    else if(unseen)return 0;
	else return 2;
}

//�ˬd�j���l�O�_�w�����Φ����~ 
int check_block(int r,int c){
	int number[10]={0};
    int unseen=0,error=0;
    int br,bc;
    
    br=(r/3)*3;
    bc=(c/3)*3;
    
    
    for(int b=0;b<=2;b++){
    	
    	for(int a=0;a<=2;a++){
    	
    	if(board[br+b][bc+a]==0){unseen=1;continue;}
    	if(number[board[br+b][bc+a]]){error=1;break;}
    	number[board[br+b][bc+a]]++;
		}
	}
	
	if(error)return 1;
    else if(unseen)return 0;
	else return 2;
}

//��J�Ʀr�ö}�l�ˬd��l 
void fill_number(int c)
{
	int br=cur_r/3*3;
	int bc=cur_c/3*3;
	if(editable[cur_r][cur_c])board[cur_r][cur_c]=c;
	for(int r=0;r<9;r++){
	for(int c=0;c<9;c++){
				has_error[r][c]=(check_horizontal(r,c)==1||check_vertical(r,c)==1||check_block(r,c)==1);
				complete[r][c]=(check_horizontal(r,c)==2||check_vertical(r,c)==2||check_block(r,c)==2);
	}
	
	
	}}

	

//���ʴ�� 
void move_cursor(char c)
{
 
    if ( (c == 'W' || c == 'w' )){
    	for(int i=1;i<=cur_r;i++){
    		if(editable[cur_r-i][cur_c]&&(cur_r-i)>=0){cur_r=cur_r-i; break;}
		}
	}
    	
	if ( (c == 'S' || c == 's' )){ 
		for(int i=1;i<=9-cur_r;i++){
    		if(editable[cur_r+i][cur_c]&&(cur_r+i)<9){cur_r=cur_r+i; break;}
}}
    
	if ( (c == 'A' || c == 'a' )){
		for(int i=1;i<=cur_c;i++){
    		if(editable[cur_r][cur_c-i]&&(cur_c-i)>=0){cur_c=cur_c-i; break; }
}}
    		
	if ( (c == 'D' || c == 'd' )){
		for(int i=1;i<=9-cur_c;i++){
    		if(editable[cur_r][cur_c+i]&&(cur_c+i)<9){cur_c=cur_c+i; break;}  
    
    }}
}
/*

void move_cursor(char c)
{
 
    if ( (c == 'W' || c == 'w' )&&(cur_r-1)>=0){
    	cur_r=cur_r-1;
		}
	
    	
	if ( (c == 'S' || c == 's' )&&(cur_r+1)<9){ 
		cur_r=cur_r+1;
}
    
	if ( (c == 'A' || c == 'a' )&&(cur_c-1)>=0){
cur_c=cur_c-1;
}
    		
	if ( (c == 'D' || c == 'd' )&&(cur_c+1)<9){
		cur_c=cur_c+1;
    
    }
}
 */

//�^�� board[i][j]�O�_��󦳿��~����B�C�B�j�椤
bool is_invalid(int r, int c)
{
     if(has_error[r][c]==true)return true;
     else return false;
}

//�^�� board[i][j]�O�_���w��������B�C�B�j�椤 
bool is_done(int r, int c)
{
    if(has_error[r][c]==false&&complete[r][c]==true)return true; 
    else return false;
}

//�ˬd�C���O�_�w�����A�Y�C�Ӯ�l�������F
bool check_win()
{ int win=1;
   
    for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++){
    		if(is_done(i,j)) continue;
    		win=0;
		}
	}
    if(win)return true;
	else return false;
}

//�^�ǿ�J�r���O�_�����ʫ��O 
bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

//�^�ǿ�J�r���O�_���Ʀr 
bool is_filling_action(char c)
{
    return (c >= '0' && c <= '9');
}


string get_styled_text(string text, string style)
{
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";//����]31�^
        if (c == 'G')
            color = "32";//���]32�^
        if (c == 'E')
            color = "41";//'E'�G����I���]41�^
        if (c == 'C')
            color = "106";//'C'�G�L��I���]106�^
        if (c == 'B')
            font = ";1";//�[�ʡ];1�^
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

//�C�L�C���e�� 
void print_board()
{
    // Flush the screen
    cout << "\x1b[2J\x1b[1;1H";

    // Print usage hint.
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-9: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      K: ", "B") << "solution" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;

    // Iterate through and print each cell.
    for (int i = 0; i < 9; ++i)
    {
        // Print horizontal divider.
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        // �C�L�C�椤���Ĥ@�ӫ������j�u�C
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // �̷��x�s�檺���A�]�w��r�˦��C
            string style = "";

            // �]�w�C�Ы��V���x�s�檺�˦��C
            if (cur_r == i && cur_c == j)
                style = "C";
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";

            // �H�˦���r�C�L�x�s��C
            // �p�G���e��0�A�h�C�L�@���I�A�_�h�C�L�Ʀr
            if (board[i][j] == 0)
                cout << get_styled_text(" �P ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // �C�L�C�Ӱ϶����������j�u�C.
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize()
{
    // Set up styled text for Windows.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    //�аO�i�s��椸��
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = !board[i][j];

    // �C�L��l�O�C
    print_board();
}


int main()
{
    char c;
    bool action_ok;

    generate_sudoku();
    initialize();
    
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))
        {
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
            action_ok = true;
            fill_number(c-48);
        }

        if (c == 'Q' || c == 'q')break;
            
        if (c == 'K' || c == 'k'){ action_ok = true; print_solution(solution);} 

        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
        
		print_board();
    }

    return 0;
}
