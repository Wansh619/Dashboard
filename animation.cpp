#include <iostream>
#include <cmath>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

typedef vector<vector<char>> Grid;

#ifdef _WIN32
int getSessionHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int getSessionWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
#else
int getSessionHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

int getSessionWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
#endif



// Fill grid with a character
void fillGrid(Grid& grid,  char c) {
    int height=grid.size();
    int width= grid[0].size();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = c;
        }
    }
}


void print_figure(Grid& grid) {
    int height=grid.size();
    int width= grid[0].size();
    cout << "\033[0;0H";  
    cout.flush();         
    int center_x = width / 2;
    int center_y = height / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int x = j - center_x;
            int y = i - center_y;
            cout<<grid[i][j];
        }
        cout << endl;
    }
}
void create_circle(Grid& grid,int c_x,int c_y, int radius, int thickness, char symbol) {
    int h=grid.size();
    int w= grid[0].size();
    int center_x = c_x;
    int center_y = c_y;
    int far_pt = (radius + thickness) * (radius + thickness);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int x = j - center_x;
            int y = i - center_y;
            int dist = x * x + y * y;

            if (dist >= (radius * radius) && dist <= far_pt) {
                grid[i][j] = symbol;
            }
        }
    }


}



void animation(int t,char symbol,double delay_sec){
    int maxRadius= 1;
    for( int i=0;i<maxRadius+5;i++){
        int windowHeight = getSessionHeight();
        int windowWidth = getSessionWidth()-1;
        maxRadius=max(windowHeight/2,windowWidth/2);
        Grid grid(windowHeight, vector<char>(windowWidth, ' '));
        int c_y=grid.size()/2;
        int c_x=grid[0].size()/2;

        create_circle(grid,c_x,c_y, i, t, symbol);
        print_figure(grid);
        usleep(delay_sec*10000);
        fillGrid(grid,' ');
        // cout<<"running empty"<<i<<endl;

        // cout<<"after delay"<<endl;
    }
}


void stream_animation(int thickness,int repeatation,char symbol,double delay_sec)
{
    for( int i=0;i<repeatation;i++){
        // cout<<"running reps"<<i<<endl;
        animation(thickness,symbol,delay_sec);
        // cout<<"run anim"<<endl;
    }
    // animation(grid,thickness,maxRadius,symbol,delay_sec);
}


int main(int argc,char* argv[]) {
    

    int repeatation=3;
    int thickness = 5;
    bool inf=false;
    double delay_sec=3;
    char symbol='.';
    
    
    for(int i=1;i<argc;i++)
    {
        string flag= argv[i];
        // cout<<"--->"<<flag;
        

        
        if( flag=="-t"){
            
            string t=argv[++i];
            thickness=stoi(t);
        }
        
        else if( flag=="-ds"){
            
            string t=argv[++i];
            delay_sec=stod(t);
        }
        
        else if( flag=="-s")
        {
            string s=argv[++i];
            symbol=s[0];
        }
        else if( flag=="-r")
        {
            string s=argv[++i];
            repeatation=stoi(s);
        }
        else if(flag=="--inf")
        {
            inf=true;
        }
        else if( flag=="--help")
        {
            cout<<"-r :: "<<"specify the repeatation of the circles DEFAULT = "<< repeatation <<endl;
            cout<<"-t :: "<<"specify the thickness of the circles DEFAULT = "<< thickness <<endl;
            cout<<"-ds ::"<<"delay time in animation DEFAULT = "<< delay_sec <<endl;
            cout<<"-s ::"<<"character symbol for drawing circle DEFAULT = "<< symbol <<endl;
            cout<<"--inf ::"<<"run for infinity DEFAULT = "<< inf <<endl;
            cout<<"--help ::"<<"help section "  <<endl;
            return 0;
        }
        else
        {
            cerr<<"INCORRECT ARGUMENT"<<endl;
            return 1;
        }
        
    }
    
    
    if(!inf){
        // cout<<"running stream"<<endl;

        stream_animation(thickness,repeatation,symbol,delay_sec);
    }
    else{
        cout<<"inf"<<endl;
        while(inf){

            animation(thickness, symbol, delay_sec);
        }
    }
    cout<<"\033[0;0H";
    return 0;
    
}
