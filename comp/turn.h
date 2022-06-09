//
// Created by l'l on 2022/5/14.
//

#ifndef ASTAR_MASTER_TURN_H
#define ASTAR_MASTER_TURN_H


#include <iostream>
#include <set>
#include <memory>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>

using std::string;
using std::vector;
using std::set;
using std::min;
using std::max;


class Point {
public:

    Point() {

    }

    double x, y, f, g, h, t;
    int id, passMid;
    string dir = "K";


    Point(double x, double y, int d) {
        this->x = x;
        this->y = y;
        id = d;
        f = 0;
        g = 0;
        h = 0;
        t = 0;
    }

    Point(double x, double y) {
        this->x = x;
        this->y = y;
        f = 0;
        g = 0;
        h = 0;
        t = 0;
    }

    ~Point(){
//        std::cout<<"point\n";
    }

//
    std::shared_ptr<Point> parent = nullptr;

    void setH(double x1, double y1, double x2, double y2) {
        if (passMid == 1)
            h = fabs(x2 - x) + fabs(y2 - y);
        else h = fabs(x2 - x) + fabs(y2 - y) + fabs(x1 - x) + fabs(y1 - y);
    }

    void setParent(std::shared_ptr<Point> par) {
        parent = par;
    }


};

struct cmp {
    bool operator()(std::shared_ptr<Point> a, std::shared_ptr<Point> b) {
        if (a->f != b->f)
            return a->f > b->f;
//        if (fabs(a->h - a->g) != fabs(b->h - b->g))return fabs(a->h - a->g) > fabs(b->h - b->g);
    }
};

std::priority_queue<std::shared_ptr<Point>, vector<std::shared_ptr<Point>>, cmp> openList;

class Rect {
public:
    double lx, ly, width, height;
    Point LT, RT, LB, RB;

    Rect() {

    }

    Rect(double _lx, double _ly, double _w, double _h) {
        lx = _lx;
        ly = _ly;
        width = _w;
        height = _h;
        LT = Point(lx, ly);
        RT = Point(lx + width, ly);
        LB = Point(lx, ly + height);
        RB = Point(lx + width, ly + height);
    }

};

class line {
public:
    Point st, ed;

    line() {

    }

    line(Point s, Point e) {
        st = s;
        ed = e;
    }
};

double cj(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool jduge(line p, line q) {
    if (std::min(p.st.x, p.ed.x) > std::max(q.st.x, q.ed.x))return false;
    if (min(p.st.y, p.ed.y) > max(q.st.y, q.ed.y))return false;
    if (min(q.st.x, q.ed.x) > max(p.st.x, p.ed.x))return false;
    if (min(q.st.y, q.ed.y) > max(p.st.y, p.ed.y))return false;

    if (cj(p.st, q.st, p.ed) * cj(p.st, p.ed, q.ed) < 0)return false;
    if (cj(q.st, p.st, q.ed) * cj(q.st, q.ed, p.ed) < 0)return false;

    return true;
}

bool onSegment(Point Pi, Point Pj, Point Q) {
    if ((Q.x - Pi.x) * (Pj.y - Pi.y) == (Pj.x - Pi.x) * (Q.y - Pi.y)  //叉乘
        //保证Q点坐标在pi,pj之间
        && min(Pi.x, Pj.x) <= Q.x && Q.x <= max(Pi.x, Pj.x)
        && min(Pi.y, Pj.y) <= Q.y && Q.y <= max(Pi.y, Pj.y))
        return true;
    else
        return false;
}

double padding = 20;

int inclose[1000], inopen[1000];
string dirs[4] = {"L", "R", "T", "B"};
int getOpposite(string a, string b) {
    return (a == "L" && b == "R") || (a == "R" && b == "L") || (a == "T" && b == "B") || (a == "B" && b == "T");
}

Rect A(100, 100, 100, 100);
Rect B(100,400, 100, 100);
std::shared_ptr<Point> startInfo, endInfo, midPoint;
std::shared_ptr<Point> startP, endP;
string onA,onB;
int onOpposite;
vector<std::shared_ptr<Point>> ans;
vector<std::shared_ptr<Point>> M;
set<double> xs, ys;

void clear() {
    while (!openList.empty()) {
        openList.pop();
    }

    for (int i = 0; i < (int) M.size(); i++) {
        M[i]->g = M[i]->f = M[i]->h = 0;
        M[i]->dir = "k";
        M[i]->parent = nullptr;
    }
    std::memset(inopen, 0, sizeof(inopen));
    std:: memset(inclose, 0, sizeof(inclose));
    ans.clear();
    xs.clear();
    ys.clear();
}

void init(){
    while (!openList.empty()) {
        openList.pop();
    }
    M.clear();
    std::memset(inopen, 0, sizeof(inopen));
    std:: memset(inclose, 0, sizeof(inclose));
    ans.clear();
    xs.clear();
    ys.clear();
}

string firstDir;

void Astar() {

    std::cout << "midpoint " << midPoint->x << " " << midPoint->y <<std::endl;
    openList.push(startInfo);
    inopen[startInfo->id] = 1;
    double fact = 1;

    while (!openList.empty()) {
        auto now = openList.top();
        std::cout << "now " << now->x << " " << now->y << " " << now->g << " " << now->f << std::endl;
        openList.pop();

        inopen[now->id] = 0;
        std::cout << "-------------" << std::endl;
        inclose[now->id] = 1;
        if (now->x == endInfo->x && now->y == endInfo->y) {
            std::cout << "endinfo " << endInfo->g << " " << endInfo->f << std::endl;
            break;
        }
        for (auto nxt: M) {
            if (now->x == nxt->x && now->y == nxt->y)continue;
            if (nxt->x == now->x || nxt->y == now->y) {
                if (jduge(line(*now, *nxt), line(A.LT, A.RB)) || jduge(line(*now, *nxt), line(A.RT, A.LB)) ||
                    jduge(line(*now, *nxt), line(B.LT, B.RB)) || jduge(line(*now, *nxt), line(B.RT, B.LB)) ||
                    inclose[nxt->id]) {
                    continue;
                }
                string dir;
                if (now->y == nxt->y) {
                    if (now->x < nxt->x)dir = "R";
                    else dir = "L";
                } else if (now->x == nxt->x) {
                    if (now->y < nxt->y)dir = "B";
                    else dir = "T";
                }
                if (now->x == startInfo->x && now->y == startInfo->y && dir != firstDir)continue;
                if (onOpposite) {
                    nxt->passMid = now->passMid;
                    if (onSegment(*now, *nxt, *midPoint))
                        nxt->passMid = 1;
                }

                if (!inopen[nxt->id]) {

                    nxt->setH(midPoint->x, midPoint->y, endInfo->x, endInfo->y);
                    nxt->parent = now;
                    nxt->dir = dir;
                    nxt->g = now->g + fabs(now->x - nxt->x) + fabs(now->y - nxt->y) + fact * (nxt->dir != now->dir);
                    nxt->f = nxt->h + nxt->g;
                    nxt->t = now->t + (nxt->dir != now->dir);
                    openList.push(nxt);
                    std::cout << nxt->x << " " << nxt->y << " " << nxt->g<<" "<<nxt->h << std::endl;
                    inopen[nxt->id] = 1;
                } else {
                    double ng = now->g + fabs(now->x - nxt->x) + fabs(now->y - nxt->y) + fact * (dir != now->dir);
                    if (ng < nxt->g) {
                        nxt->setH(midPoint->x, midPoint->y, endInfo->x, endInfo->y);
                        nxt->parent = now;
                        nxt->dir = dir;
                        nxt->g = ng;
                        nxt->f = nxt->h + nxt->g;
                        nxt->t = now->t + (nxt->dir != now->dir);
                      std::  cout << nxt->x << " " << nxt->y << " " << nxt->g << " " << nxt->h << std::endl;
                    }
                }
            }
        }
    }

}

int isTurn(Point a, Point b, Point c) {
    if (a.x == c.x) {
        if (min(a.y, c.y) < b.y && b.y < max(a.y, c.y))return 0;
    }
    if (a.y == c.y) {
        if (min(a.x, c.x) < b.x && b.x < max(a.x, c.x))return 0;
    }
    return 1;
}

int checkPathValid() {
    for (int i = 0; i < ans.size() - 1; i++) {
        if (ans[i]->x != ans[i + 1]->x && ans[i]->y != ans[i + 1]->y)return 0;
    }
    return 1;
}

std::pair<int,double> getTurn() {
    auto t = endInfo;
    ans.push_back(endP);
    while (1) {
        std::cout << t->x << " " << t->y << " " << t->t << " " << t->dir << std::endl;
        ans.push_back(t);
        t = t->parent;
        if (t == nullptr)break;
    }
    ans.push_back(startP);
    std:: reverse(ans.begin(), ans.end());
    for (auto val: ans) {
        std::cout << val->x << "," << val->y << " ";
    }
    int res = 0;
    int siz = ans.size();
    for (int i = 1; i + 1 < siz; i++) {
        res += isTurn(*ans[i - 1], *ans[i], *ans[i + 1]);
    }

    if (!checkPathValid())res = 10000;
    std:: pair<int,double>result;
    result.first = res;
    for(int i=0;i<siz-1;i++){
        result.second+=fabs(ans[i]->x-ans[i+1]->x)+fabs(ans[i]->y-ans[i+1]->y);
    }
    return result;
}


string getOpDir(string a) {
    if (a == "L")return "R";
    if (a == "R")return "L";
    if (a == "T")return "B";
    if (a == "B")return "T";
}

void ensurePadding() {
    padding = min(padding, min(fabs(startP->x - endP->x) / 2, fabs(startP->y - endP->y) / 2));
}

string getOnDir(Rect a,Point p){
    if(p.x == a.LT.x){
        return "L";
    }
    else if(p.x == a.RB.x){
        return "R";
    }
    else if(p.y == a.LT.y){
        return "T";
    }
    else if(p.y == a.RB.y){
        return "B";
    }
}
static int cnt = 0;
static void turnPoint() {
    init();
    startP = std::make_shared<Point>(200, 150), endP = std::make_shared<Point>(150, 400);
    onA = getOnDir(A,*startP);
    onB = getOnDir(B,*endP);

//    ensurePadding();

    xs.insert(A.LT.x);
    xs.insert(A.RB.x);
    xs.insert(B.LT.x);
    xs.insert(B.RB.x);
    xs.insert(A.LT.x - padding);
    xs.insert(A.RB.x + padding);
    xs.insert(B.LT.x - padding);
    xs.insert(B.RB.x + padding);
    xs.insert(startP->x);
    xs.insert(endP->x);

    ys.insert(A.LT.y);
    ys.insert(A.RB.y);
    ys.insert(B.LT.y);
    ys.insert(B.RB.y);
    ys.insert(A.LT.y - padding);
    ys.insert(A.RB.y + padding);
    ys.insert(B.LT.y - padding);
    ys.insert(B.RB.y + padding);
    ys.insert(startP->y);
    ys.insert(endP->y);

    onOpposite = getOpposite(onA, onB);


    int t1 = 0;
    if (onA == "R" || onA == "L") {
        if (onA == "R") {
            startInfo = std::make_shared<Point>(A.RB.x + padding, startP->y, t1);
        } else {
            startInfo = std::make_shared<Point>(A.LB.x - padding, startP->y, t1);
        }
    } else if (onA == "T" || onA == "B") {
        if (onA == "T") {
            startInfo = std::make_shared<Point>(startP->x, A.LT.y - padding, t1);

        } else {
            startInfo = std::make_shared<Point>(startP->x, A.RB.y + padding, t1);
        }
    }

    t1++;
    if (onB == "R") {
        endInfo = std::make_shared<Point>(B.RB.x + padding, endP->y, t1);

    } else if (onB == "L") {
        endInfo = std::make_shared<Point>(B.LB.x - padding, endP->y, t1);

    } else if (onB == "T") {
        endInfo = std::make_shared<Point>(endP->x, B.LT.y - padding, t1);
    } else {
        endInfo = std::make_shared<Point>(endP->x, B.RB.y + padding, t1);
    }
    midPoint = std::make_shared<Point>((startInfo->x + endInfo->x) / 2, (startInfo->y + endInfo->y) / 2);

    xs.insert(midPoint->x);
    ys.insert(midPoint->y);


    M.push_back(startInfo);
    M.push_back(endInfo);
    for (auto x: xs) {
        for (auto y: ys) {
            if (x == startInfo->x && y == startInfo->y) continue;
            if (x == endInfo->x && y == endInfo->y) continue;
            int t = M.size();
            M.push_back(std::make_shared<Point>(x, y, t));
        }
    }


    for (auto v: M) {
        std::cout << "M " << v->x << " " << v->y << std::endl;
    }

    std::cout<<"onA "<<onA<<std::endl;
    std::cout<<"onB "<<onB<<std::endl;


    string opA = getOpDir(onA);
    std::pair<int,double>minTurn = std::make_pair(1000,1000000);
    vector<std::shared_ptr<Point>> result;
    for (int i = 0; i < 4; i++) {
        if (dirs[i] == opA)continue;
        firstDir = dirs[i];
        Astar();
        std::cout << "finish A*" << std::endl;
        std::pair<int,double> turn = getTurn();
        std::cout <<"turn "<< turn.first <<" "<<turn.second << std::endl;
        if (minTurn > turn) {
            minTurn = turn;
            result = ans;
        }
        clear();
    }
    std::cout << "result\n";
    for (auto v: result) {
        std::cout << v->x << "," << v->y << " ";
    }

}

#endif //ASTAR_MASTER_TURN_H
