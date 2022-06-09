var Node = function (x, y) {
    this.x = x;
    this.y = y;
    this.g = 0; // 到起点的长度
    this.h = 0; // 到终点的长度
    this.p = null; // 父节点
    this.passMid = 0;
    this.dir = "k";
}

var Rect = function (x, y, w, h) {
    this.x = x;
    this.y = y;
    this.width = w; // 到起点的长度
    this.height = h; // 到终点的长度
    this.LT = new Node(x, y);
    this.RT = new Node(x + w, y);
    this.LB = new Node(x, y + h);
    this.RB = new Node(x + w, y + h);
}


/**
 * 实现一个最小堆，方便从OpenSet中选择最小代价的点
 */
var heapMin = function () {
    this.set = [];
}

heapMin.prototype.adjust = function (index) {
    let len = this.set.length,
        l = index * 2 + 1,
        r = index * 2 + 2,
        min = index,
        node = null;

    if (l <= len - 1 && this.set[min].g + this.set[min].h > this.set[l].g + this.set[l].h) {
        min = l;
    }
    if (r <= len - 1 && this.set[min].g + this.set[min].h > this.set[r].g + this.set[r].h) {
        min = r;
    }

    // 如果min发生改变，则需要进行交换，并继续递归min子树
    if (min != index) {
        node = this.set[min];
        this.set[min] = this.set[index];
        this.set[index] = node;
        this.adjust(min);
    }
}

/**
 * 向最小堆中添加一个元素
 */
heapMin.prototype.push = function (node) {
    // 添加到数组尾部
    this.set.push(node);

    // 调整堆
    for (let i = Math.floor(this.set.length / 2) - 1; i >= 0; i--) {
        this.adjust(i);
    }

}

/**
 * 从最小堆中移除顶部元素
 */
heapMin.prototype.pop = function () {
    // 移除顶部元素，为最小元素
    let node = this.set.shift();

    // 调整堆
    this.adjust(0);

    return node;
}

/**
 * 检查堆是否为空
 */
heapMin.prototype.empty = function () {
    return this.set.length > 0 ? false : true;
}

/**
 * 检查堆是否包含指定元素
 */
heapMin.prototype.contain = function (node) {
    for (let len = this.set.length, i = 0; i < len; i++) {
        if (this.set[i].x === node.x && this.set[i].y === node.y) return true;
    }
    return false;
}


/**
 * Set类
 */
function Set() {
    this.set = [];
}

Set.prototype.push = function (node) {
    this.set.push(node);
}

Set.prototype.pop = function () {
    return this.set.pop();
}

Set.prototype.contain = function (node) {
    for (let len = this.set.length, i = 0; i < len; i++) {
        if (this.set[i].x === node.x && this.set[i].y === node.y) return true;// 存在
    }
    return false;
}


/**
 * AStarPathFinding
 *
 * W：地图的宽度
 * H：地图的高度
 * map：地图数组，0表示可以通过，1表示不可以通过
 *
 */
function getOnDir(a, p) {
    if (p.x == a.LT.x) {
        return "L";
    } else if (p.x == a.RB.x) {
        return "R";
    } else if (p.y == a.LT.y) {
        return "T";
    } else if (p.y == a.RB.y) {
        return "B";
    }
}

function getOpposite(a, b) {
    return (a == "L" && b == "R") || (a == "R" && b == "L") || (a == "T" && b == "B") || (a == "B" && b == "T");
}

function getOpDir(a) {
    if (a == "L") return "R";
    if (a == "R") return "L";
    if (a == "T") return "B";
    if (a == "B") return "T";
}

function unique(arr){
    let newArr = [];
    for(let i = 0; i < arr.length; i++){
        if(newArr.indexOf(arr[i]) == -1){
            newArr.push(arr[i])
        }
    }
    return newArr;
}


function AStarPathFinding(S,E) {
    let x1 = S["x"], y1 = S["y"], w1 = S["w"], h1 = S["h"], x2 = E["x"], y2 = E["y"],
        w2 = E["w"], h2 = E["h"], sx = S["sx"], sy = S["sy"], ex = E["sx"], ey = E["sy"];

    let start = new Rect(x1, y1, w1, h1);
    let end = new Rect(x2, y2, w2, h2);
    let startPoint = new Node(sx, sy);
    let endPoint = new Node(ex, ey);
    let onA = getOnDir(start, startPoint);
    let onB = getOnDir(end, endPoint);
    let padding = 20;
    // padding = Math.min(padding, Math.min(Math.abs(sx - ex) / 2, Math.abs(sy - ey) / 2));
    let xs = []
    let ys = [];
    xs.push(start.LT.x);
    xs.push(start.RB.x);
    xs.push(end.LT.x);
    xs.push(end.RB.x);
    xs.push(start.LT.x - padding);
    xs.push(start.RB.x + padding);
    xs.push(end.LT.x - padding);
    xs.push(end.RB.x + padding);
    xs.push(startPoint.x);
    xs.push(endPoint.x);

    ys.push(start.LT.y);
    ys.push(start.RB.y);
    ys.push(end.LT.y);
    ys.push(end.RB.y);
    ys.push(start.LT.y - padding);
    ys.push(start.RB.y + padding);
    ys.push(end.LT.y - padding);
    ys.push(end.RB.y + padding);
    ys.push(startPoint.y);
    ys.push(endPoint.y);


    let startInfo = null, endInfo = null;
    if (onA == "R" || onA == "L") {
        if (onA == "R") {
            startInfo = new Node(start.RB.x + padding, startPoint.y);
        } else {
            startInfo = new Node(start.LB.x - padding, startPoint.y);
        }
    } else if (onA == "T" || onA == "B") {
        if (onA == "T") {
            startInfo = new Node(startPoint.x, start.LT.y - padding);

        } else {
            startInfo = new Node(startPoint.x, start.RB.y + padding);
        }
    }


    if (onB == "R") {
        endInfo = new Node(end.RB.x + padding, endPoint.y);

    } else if (onB == "L") {
        endInfo = new Node(end.LB.x - padding, endPoint.y);

    } else if (onB == "T") {
        endInfo = new Node(endPoint.x, end.LT.y - padding);
    } else {
        endInfo = new Node(endPoint.x, end.RB.y + padding);
    }
    let midPoint = new Node((startInfo.x + endInfo.x) / 2, (startInfo.y + endInfo.y) / 2);

    xs.push(midPoint.x);
    ys.push(midPoint.y);

    xs = unique(xs);
    ys = unique(ys);




    let opA = getOpDir(onA);
    let minTurn = {
        "length": 1000000,
        "turn": 1000000,
        "ans": []
    }

    let dirs = ["B","L", "R",  "T"];
    console.log("onA")
    console.log(onA)
    console.log("onB")
    console.log(onB)
    let M = [];
    for (let item of dirs) {
        console.log("item");
        console.log(item);
        if (item == opA) continue;

        for (let itemx of xs.values()) {
            for (let itemy of ys.values()) {
                M.push(new Node(itemx, itemy));
            }
        }
        console.log("M\n\n\n");
        for (let t of M) {
            console.log(t);
        }
        let tmp = findPath(start, startInfo, onA, startPoint, end, endInfo, onB, endPoint, item, M)
        M =[];
        if (minTurn["turn"] > tmp["turn"] ||
            (minTurn["turn"] == tmp["turn"] && minTurn["length"] > tmp["length"])) {
            minTurn = tmp;
        }
    }
    console.log("final \n\n\n");
    for (let t of minTurn["ans"]) {
        console.log(t);
    }
    return minTurn["ans"];
}

/**
 * 计算距离
 *
 * 采用曼哈顿估量算法
 */
function calcDistance(startNode, endNode) {
    return (startNode && endNode) ?
        Math.abs(startNode.x - endNode.x) + Math.abs(startNode.y - endNode.y)
        :
        -1;
}

/**
 * 查找路径
 *
 * 1 初始化起始点，计算g，h
 * 2 将起始点加入到OpenSet中
 * 3 当OpenSet不为空的时候，进入循环
 * 3.1 从OpenSet中取出最小点，设为当前点
 * 3.2 循环遍历当前点的邻居点
 * 3.2.1 如果邻居点不可通过（为墙壁）或者已经在CloseSet中，就略过continue
 * 3.2.2 如果不在OpenSet中，计算FGH数值，并加入到CloseSet的尾部
 * 3.3 循环遍历邻居点结束
 * 4 OpenSet循环结束
 */
function cj(a, b, c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

function jduge(p, q) {
    let pst = p["st"];
    let ped = p["ed"];
    let qst = q["st"];
    let qed = q["ed"];
    if (Math.min(pst.x, ped.x) > Math.max(qst.x, qed.x)) return false;
    if (Math.min(pst.y, ped.y) > Math.max(qst.y, qed.y)) return false;
    if (Math.min(qst.x, qed.x) > Math.max(pst.x, ped.x)) return false;
    if (Math.min(qst.y, qed.y) > Math.max(pst.y, ped.y)) return false;

    if (cj(pst, qst, ped) * cj(pst, ped, qed) < 0) return false;
    if (cj(qst, pst, qed) * cj(qst, qed, ped) < 0) return false;

    return true;
}

function onSegment(Pi, Pj, Q) {
    if ((Q.x - Pi.x) * (Pj.y - Pi.y) == (Pj.x - Pi.x) * (Q.y - Pi.y)  //叉乘
        //保证Q点坐标在pi,pj之间
        && Math.min(Pi.x, Pj.x) <= Q.x && Q.x <= Math.max(Pi.x, Pj.x)
        && Math.min(Pi.y, Pj.y) <= Q.y && Q.y <= Math.max(Pi.y, Pj.y))
        return 1;
    else
        return 0;
}

function isTurn(a, b, c) {
    if (a.x == c.x) {
        if (Math.min(a.y, c.y) < b.y && b.y < Math.max(a.y, c.y)) return 0;
    }
    if (a.y == c.y) {
        if (Math.min(a.x, c.x) < b.x && b.x < Math.max(a.x, c.x)) return 0;
    }
    return 1;
}

function checkPathValid(ans) {
    for (let i = 0; i < ans.length - 1; i++) {
        if (ans[i].x != ans[i + 1].x && ans[i].y != ans[i + 1].y) return 0;
    }
    return 1;
}

findPath = function (start, startInfo, onA, startPoint, end, endInfo, onB, endPoint, firstDir, M) {
    let OpenSet = new heapMin(),
        CloseSet = new Set(),
        curNode = null;
    let onOpposite = getOpposite(onA, onB);
    console.log("opposite")
    console.log(onOpposite);
    let midPoint = new Node((startInfo.x + endInfo.x) / 2, (startInfo.y + endInfo.y) / 2);
    console.log("midpoint")
    console.log(midPoint);
    OpenSet.push(startInfo);

    // 循环遍历OpenSet直到为空
    while (!OpenSet.empty()) {
        curNode = OpenSet.pop();
        CloseSet.push(curNode);

        console.log("cur");
        console.log(curNode);

        if (curNode.x === endInfo.x && curNode.y === endInfo.y) {
            // return CloseSet.set;
            console.log("endinfo")
            console.log(endInfo);
            break;
        }

        for (let nxt of M) {

            if (nxt.x == curNode.x && nxt.y == curNode.y) continue;
            if (nxt.x == curNode.x || nxt.y == curNode.y){
                if (jduge({"st": curNode, "ed": nxt}, {"st": start.LT, "ed": start.RB}) ||
                    jduge({"st": curNode, "ed": nxt}, {"st": start.RT, "ed": start.LB}) ||
                    jduge({"st": curNode, "ed": nxt}, {"st": end.LT, "ed": end.RB}) ||
                    jduge({"st": curNode, "ed": nxt}, {"st": end.RT, "ed": end.LB})
                ) continue;
                if (CloseSet.contain(nxt)) continue;
                let dir;
                if (curNode.y == nxt.y) {
                    if (curNode.x < nxt.x) dir = "R";
                    else dir = "L";
                } else if (curNode.x == nxt.x) {
                    if (curNode.y < nxt.y) dir = "B";
                    else dir = "T";
                }
                if (curNode.x == startInfo.x && curNode.y == startInfo.y && dir != firstDir) continue;
                if (onOpposite) {
                    nxt.passMid = curNode.passMid;
                    if (onSegment(curNode, nxt, midPoint))
                        nxt.passMid = 1;
                }
                // 不存在，加入到OpenSet集合
                if (!OpenSet.contain(nxt)) {
                    nxt.dir = dir;
                    nxt.g = curNode.g + calcDistance(nxt, curNode) + (nxt.dir != curNode.dir);
                    if (nxt.passMid == 1) {
                        nxt.h = calcDistance(nxt, endInfo);
                    } else {
                        nxt.h = calcDistance(nxt, endInfo) + calcDistance(nxt, midPoint);
                    }
                    // 更新父节点，便于之后路径查找
                    nxt.p = curNode;
                    OpenSet.push(nxt);
                    console.log("nxt")
                    console.log(nxt);
                } else {
                    let ng = curNode.g + calcDistance(nxt, curNode) + (dir != curNode.dir);
                    if (ng < nxt.g) {
                        nxt.dir = dir;
                        nxt.g = ng;
                        if (nxt.passMid == 1) {
                            nxt.h = calcDistance(nxt, endInfo);
                        } else {
                            nxt.h = calcDistance(nxt, endInfo) + calcDistance(nxt, midPoint);
                        }
                        // 更新父节点，便于之后路径查找
                        nxt.p = curNode;
                        console.log("nxt")
                        console.log(nxt);
                    }
                }
            }

        }
    }
    let t = curNode;
    console.log("cur ")
    console.log(curNode);
    console.log("t")
    console.log(t);
    let ans = [];
    ans.push(endPoint);
    while (1) {
        ans.push(t);
        t = t.p;
        if(t==null)break;
    }
    ans.push(startPoint);
    let res = ans.reverse();
    console.log("res\n\n\n");
    for (let val of res) {
        console.log(val);
    }
    let turn = 0;
    let sz = res.length;
    for (let i = 1; i + 1 < sz; i++) {
        turn += isTurn(res[i - 1], res[i], res[i + 1]);
    }

    if (!checkPathValid(res)) turn = 10000;
    let len = 0;
    for (let i = 0; i < sz - 1; i++) {
        len += Math.abs(res[i].x - res[i + 1].x) + Math.abs(res[i].y - res[i + 1].y);
    }

    let result = {
        "length": len,
        "turn": turn,
        "ans": res
    }
    return result;
}

/**
 * 打印寻路结果地图
 */
printMap = function (s, e) {
    if (s.x < 0 || s.x > this.W - 1 || s.y < 0 || s.y > this.H - 1 || e.x < 0 || e.x > this.W - 1 || e.y < 0 || e.y > this.H - 1)
        return;
    let arr = this.findPath(s, e);

    if (arr == null) {
        console.log('Not found Path...');
        return;
    }

    let map = this.map.slice(),
        node = arr.pop();

    while (node !== null) {
        map[node.y][node.x] = ((s.x === node.x && s.y === node.y) || (e.x === node.x && e.y === node.y)) ? '+' : '*';
        node = node.p;
    }

    for (let i = 0; i < this.H; i++) {
        let temp = [];
        for (let j = 0; j < this.W; j++) {
            temp[j] = map[i][j];
        }
        console.log(temp.join(' ') + '<br />');
    }

}


