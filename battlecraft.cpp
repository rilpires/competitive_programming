#include <iostream>
#include <string>

using namespace std;


struct Grid{
    int width;
    int height;
    int last_x;
    int last_y;
    short* values;
    Grid( int w , int h ){
        width = w; height = h;
        values = new short[w*h];
        for( int y = 0 ; y < height ; y++ )
        for( int x = 0 ; x < width ; x++ )
            values[ x + y*w ] = 0;
    }
    ~Grid(){
        delete[] values;
    }

    short read( int x , int y ){
        x = x % width; y = y % height;
        return values[ x + y*width ];
    }
    void fill( int x , int y ){
        x = x % width; y = y % height;
        //cout << x << " , " << y << endl;
        if( last_x == x || last_y == y || x - y == last_x - last_y || x + y == last_x + last_y )
            if( x != 0 && y != 0 )
                cout << "Problema! Do " << last_x << "," << last_y << " para o "  << x << " , " << y << endl;
        values[ x + y*width ] = 1;
        last_x = x; last_y = y;
    }


};

int main(){
    int W , H , T , x , y , min_y , case_number = 1;
    cin >> T;
    while( T-- ){
        cin >> W >> H ;
        Grid grid(W,H);
        bool possible = true;
        if( W <= 3 || H <= 3 ){
            cout << "Case #" << case_number++ << ": Impossible" << endl;
            continue;
        }
        x = 0; min_y = 0 ; y = 0 ;
        for( int i = 0 ; i < H * ((W+1)/2) ; i++ ){
            if( grid.read(x, (min_y+y) ) ){
                possible = false;
                break;
            }
            grid.fill( x , (min_y+y) );
            x += 2;
            if( y == H-1 ){
                min_y++;
                y = 0;
            }else y++;
        }
        if( !possible ){
            cout << "Case #" << case_number++ << ": Impossible" << endl;
            continue;
        }
        x = 1; min_y = 1; ; y = 0 ;
        for( int i = 0 ; i < H * ((W+1)/2) ; i++ ){
            if( grid.read(x, (min_y+y) ) ){
                possible = false;
                break;
            }
            grid.fill( x , (min_y+y) );
            x += 2;
            if( y == H-1 ){
                min_y++;
                y = 0;
            }else y++;
        }
        if( !possible ){
            cout << "Case #" << case_number++ << ": Impossible" << endl;
            continue;
        }

        // Deu!
        cout << "Case #" << case_number++ << ": Possible" << endl;

    }

}
