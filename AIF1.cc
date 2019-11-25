#include "Player.hh"
#include <queue>
#include <vector>
#include <string>
#include <climits>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME FirstBFS


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

private:

  typedef vector<vector<bool>> matrixB;
  typedef vector<int> filaI;
  typedef vector<filaI> matrixI;

  //Taulell de joc
  vector<vector<char>> gBoard;
  queue<pair<int, int>> Q;
  map<int, queue<pair<int, int>>> id_move;
  vector<pair<int, int>> moves = {{0,1}, {0,-1}, {1,0}, {-1,0},{1,1}, {-1,-1}, {1,-1}, {-1,1} };

  //vector<int> 

  vector<Dir> movementsdwarves = {Bottom, Top, Right, Left, BR, TL, RT, LB};
  vector<Dir> movementswizards = {Bottom, Right, Top, Left};

  void initial_config() {
    init_grid();
    //initmap_id_move();
  }

  void init_grid() {
    vector<char> v(60);
    vector<vector<char>> u(60, v);
    gBoard = u;
    for (int i = 0; i < 60; i++) {
      for (int j = 0; j < 60; j++) {
        Cell aux = cell(i, j);
        if (aux.treasure) gBoard[i][j] = 't';
        else {
          if (aux.type == Cave) gBoard[i][j] = ' ';
          else if (aux.type == Abyss) gBoard[i][j] = 'A';
          else if (aux.type == Granite) gBoard[i][j] = 'X';
          else if (aux.type == Rock) gBoard[i][j] = '.';
        }
      }
    }
  }

  Dir convert_posTOdir(const Pos& from, const Pos& to) {
    if (pos_ok(to.i, to.j)) {
      if (from.i == to.i) {
        if (from.j == to.j) return None;
        else if (from.j+1 == to.j) return Right;
        else if (from.j-1 == to.j) return Left;
      }
      else if (from.i+1 == to.i) {
        if (from.j == to.j) return Bottom;
        else if (from.j+1 == to.j) return BR;
        else if (from.j-1 == to.j) return LB;
      }
      else if (from.i-1 == to.i) {
        if (from.j == to.j) return Top;
        else if (from.j+1 == to.j) return RT;
        else if (from.j-1 == to.j) return TL;
      }     
    }
    else return None;
  }

  Dir convert_posTOdir(int i, int j, int x, int y) {
    if (pos_ok(x, y)) {
      if (i == x) {
        if (j == y) return None;
        else if (j+1 == y) return Right;
        else if (j-1 == y) return Left;
      }
      else if (i+1 == x) {
        if (j == y) return Bottom;
        else if (j+1 == y) return BR;
        else if (j-1 == y) return LB;
      }
      else if (i-1 == x) {
        if (j == y) return Top;
        else if (j+1 == y) return RT;
        else if (j-1 == y) return TL;
      }     
    }
    return None;
  }

  void initmap_id_move() {

  }

  void walkPath(const vector<Dir>& path, int unitID, int& act) {
    command(unitID, path[act]);
  }

  bool is_wizard(int id) {
    for (auto x: wizards(me())) if (x == id) return true;
    return false;
  }

  bool search(int i, int j, queue<pair<int, int>>& PendingM, matrixB& visited){
    if (pos_ok(i, j)) {
      if (not visited[i][j]) {
        visited[i][j] = true;
        if (gBoard[i][j] == 'X') return false;
        else if (gBoard[i][j] == 't') {
          PendingM.push({i, j});
          return true;
        }
        else {
          PendingM.push({i, j});
          //if (round() == 199) cerr << i << "    " << j << endl;
          return (search(i+1, j, PendingM, visited) or 
                  search(i-1, j, PendingM, visited) or
                  search(i, j+1, PendingM, visited) or
                  search(i, j-1, PendingM, visited) or
                  search(i+1, j+1, PendingM, visited) or
                  search(i-1, j-1, PendingM, visited) or
                  search(i+1, j-1, PendingM, visited) or
                  search(i-1, j+1, PendingM, visited));
        }
      }
      return false;
    }
    return false;
  }

  queue<pair<int, int>> bfs(int x0, int y0) {

    int f = gBoard.size(), c = gBoard[0].size();
    matrixI dist(f, filaI(c, INT_MAX));

    queue<pair<int, int>> pend;
    queue<pair<int, int>> Q;
    dist[x0][y0] = 0;
    Q.push({x0, y0});

    while (not Q.empty()) {

      pair<int, int> p = Q.front();
      Q.pop();

      
      //if (M[p.first][p.second] == 't') return dist[p.first][p.second];

      for (pair<int, int> pp : moves) {

        pair<int, int> pos = {pp.first + p.first, pp.second + p.second};

        if (pos_ok(pos.first, pos.second) and dist[pos.first][pos.second] == INT_MAX) {
          Q.push(pos);
          Cell aux = cell(pos.first, pos.second);
          if (aux.owner != me() and aux.type == Cave and not is_wizard(aux.id)) pend.push(pos);
          dist[pos.first][pos.second] = dist[p.first][p.second]+1;
        }
      }
    }
    return pend;
    //return -1;
  }

  string coutDIR(Dir d) {
    if (d == 0) return "Bottom";
    else if (d == 1) return "BR";
    else if (d == 2) return "Right";
    else if (d == 3) return "RT";
    else if (d == 4) return "Top";
    else if (d == 5) return "TL";
    else if (d == 6) return "Left";
    else if (d == 7) return "LB";
    else return "None";
  }
  
  bool check_cave(Pos p, pair<int, int> pp) {

    for (pair<int, int> pp: moves) {
      pair<int, int> pos = {pp.first + p.i, pp.second + p.j};
      if (pos_ok(pos.first, pos.second) and cell(pos.first, pos.second).type == Cave) {
        pp = pos;
        return true;
      }
    }
    pp = {0, 0};
    return false;
  }

  Dir oposed_dirD(int f, int c, int x, int y) {
    int offx = f-x;
    int offy = c-y;
    if (x == 1 and y == 0) return Bottom;
    else if (x == -1 and y == 0) return Top;
    else if (x == 0 and y == 1) return Right;
    else if (x == 0 and y == -1) return Left;
    else if (x == 1 and y == 1) return BR;
    else if (x == -1 and y == -1) return TL;
    else if (x == -1 and y == 1) return RT;
    else if (x == 1 and y == -1) return LB;
    return None;
  }

  bool neutral_enemies_near(int i, int j, Dir& opo) {
    for (pair<int, int> pp: moves) {
      pair<int, int> pos = {pp.first + i, pp.second + j};
      if (pos_ok(pos.first, pos.second)) {
        Cell aux = cell(pos.first, pos.second);
        int id = aux.id;
        for (auto x: trolls()) 
          if (id == x) {
            opo = oposed_dirD(i, j, pos.first, pos.second);
            return true;
          }
        for (auto x: orcs()) 
          if (id == x) {
            opo = oposed_dirD(i, j, pos.first, pos.second);
            return true;
          }
      }
    }
    return false;
  }

  void move_dwarves() {
    vector<int> W = dwarves(me());
   
    for (auto id: W) {
      Unit u = unit(id);
      int randint = random(0,7);
      matrixB visited(60, vector<bool>(60, false));
      queue<pair<int, int>> Q = bfs(u.pos.i, u.pos.j);
      //bool treasure = search(u.pos.i, u.pos.j, Q, visited);
      //if (not Q.empty()) Q.pop();
      //Q.pop();
      pair<int, int> aux = Q.front();
      //id_move[id].pop();
      Dir d = convert_posTOdir(u.pos.i, u.pos.j, aux.first, aux.second);
      //cout << coutDIR(d) << "--";

      Dir auxd = None;
      if (neutral_enemies_near(u.pos.i, u.pos.j, auxd)) command(id, auxd);
      else if (d == None) {

        while(not pos_ok(u.pos+auxd)) {
          randint = random(0,7);
          auxd = movementsdwarves[randint];
        }
        command(id, movementsdwarves[randint]);
        /*pair<int, int> avail;
        if (check_cave(u.pos, avail)) {
          command(id, convert_posTOdir(u.pos.i, u.pos.j, avail.first, avail.second));
        }*/
      }
      else command(id, d);
    }
  }

  void move_wizards() {
    vector<int> W = wizards(me()); 
    for (auto id: W) {
      int randint = random(0,3);
      Dir auxd = movementsdwarves[randint];
      Unit u = unit(id);
      while(not pos_ok(u.pos+auxd) /*or (cell(u.pos+auxd).type != Cave and cell(u.pos+auxd).type != Outside)*/) {
        randint = random(0,7);
        auxd = movementsdwarves[randint];
      }
      command(id, movementswizards[randint]);
    }
  }

  void visualize_board() {
    if (round() == 199) {
      for (auto x: gBoard) {
        for (auto v: x) cerr << v << " ";
          cerr << endl;
      }
      cerr << endl;
    }
  };

  /**
   * Play method, invoked once per each round.
   */

public:

  virtual void play () {
    /*if (round() == 1) { 
    }*/
    initial_config();
    /// bfs a Balrog
    move_wizards();
    move_dwarves();
    //visualize_board();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
