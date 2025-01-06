#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


int solution[9][9];
bool row_used[9][10];//[行][數字]
bool col_used[9][10];
bool block_used[9][10];

int board[9][9];
bool editable[9][9];
bool has_error[9][9]={{false},{false}};
bool complete[9][9]={{false},{false}};

int cur_r = 0, cur_c = 0;//鼠標位置 

// 重置棋盤和使用狀態
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

// 檢查數字是否可以放在指定位置
bool can_use(int row, int col, int num) {
    int block_flag = (row / 3) * 3 + (col / 3);//編號大格 
    return !row_used[row][num] &&
           !col_used[col][num] &&
           !block_used[block_flag][num];
}

// 記錄數字使用狀態
void mark_used(int row, int col, int num, bool is_used) {
    int block_flag = (row / 3) * 3 + (col / 3);
    row_used[row][num] = is_used;
    col_used[col][num] = is_used;
    block_used[block_flag][num] = is_used;
}

// 隨機排列1-9的數字
void shuffle_numbers(int numbers[]) {
    for (int i = 0; i < 9; i++) {
        numbers[i] = i + 1;
    }
    random_shuffle(numbers, numbers + 9); // 隨機打亂數字
}

// 解數獨的遞迴函數
bool solve(int row, int col) {
    if (row == 9) return true;
    if (col == 9) return solve(row + 1, 0);
    if (solution[row][col] != 0) return solve(row, col + 1);

    int numbers[9];
    shuffle_numbers(numbers); // 隨機排列數字

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

// 生成數獨遊戲
void generate_sudoku() {
    srand(time(NULL));
    reset_board();

    // 生成完整解
    solve(0, 0);

    // 複製解
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = solution[i][j];
        }
    }

    // 移除數字以生成題目
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

// 列印解答 
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




 
//檢查橫列格子是否已完成或有錯誤 
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

//檢查直行格子是否已完成或有錯誤 
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

//檢查大格格子是否已完成或有錯誤 
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

//填入數字並開始檢查格子 
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

	

//移動游標 
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

//回傳 board[i][j]是否位於有錯誤的行、列、大格中
bool is_invalid(int r, int c)
{
     if(has_error[r][c]==true)return true;
     else return false;
}

//回傳 board[i][j]是否位於已完成的行、列、大格中 
bool is_done(int r, int c)
{
    if(has_error[r][c]==false&&complete[r][c]==true)return true; 
    else return false;
}

//檢查遊戲是否已結束，即每個格子都完成了
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

//回傳輸入字元是否為移動指令 
bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

//回傳輸入字元是否為數字 
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
            color = "31";//紅色（31）
        if (c == 'G')
            color = "32";//綠色（32）
        if (c == 'E')
            color = "41";//'E'：紅色背景（41）
        if (c == 'C')
            color = "106";//'C'：淺綠背景（106）
        if (c == 'B')
            font = ";1";//加粗（;1）
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

//列印遊戲畫面 
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

        // 列印每行中的第一個垂直分隔線。
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // 依照儲存格的狀態設定文字樣式。
            string style = "";

            // 設定遊標指向的儲存格的樣式。
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

            // 以樣式文字列印儲存格。
            // 如果內容為0，則列印一個點，否則列印數字
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // 列印每個區塊的垂直分隔線。.
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

    //標記可編輯單元格
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = !board[i][j];

    // 列印初始板。
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
