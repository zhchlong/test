//
// Created by l'l on 2022/5/23.
//

#include "hexagon.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Hexagon::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("hexagon");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形

        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点
        Control = createCorePoint("Control", getX()+getWidth()/4,getY()+getHeight()/2);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (nx > getX() + getWidth() / 2) Control->setX(getX() + getWidth()/2); // 不允许超过宽度的1/2
            if (nx < getX()) Control->setX(getX()); // 不允许低于矩形的X坐标
        });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Hexagon::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &Hexagon::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Hexagon &>(comp);
        // 拷贝关键点位置
        *Control = *(p.Control);

        return *this;
    }
    // 序列化，并记录已操作的
    void Hexagon::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Hexagon::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        Control = corePoints["Control"];


        return *this;
    }

    //// Basics虚接口
    void Hexagon::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double d = Control->getX() - getX(); // 记录控制点到矩形左边的距离
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, 0); // 只允许横向移动
            corePointMoving = false;
        } else { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            // 更新控制点
            if (d > getWidth() / 2) d = getWidth() / 2; // 不允许超过宽度的1/2
            *Control = createPoint(getX()+d, getY()+getHeight()/2); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string Hexagon::getPath() const {

        auto d = Control->getX() - getX();
        auto tl = createPoint(getX()+d,getY());
        auto tr = createPoint(getX()+getWidth()-d,getY());
        auto bl = createPoint(tl.get_x(),getY()+getHeight());
        auto br = createPoint(tr.get_x(),getY()+getHeight());
        auto ml = createPoint(getX(),getY()+getHeight()/2);
        auto mr = createPoint(getX()+getWidth(),getY()+getHeight()/2);

        std::stringstream ss;

        ss << "M " << bl.get_x()<<" "<<bl.get_y()<<" ";
        ss <<"L "<<ml.get_x()<<" "<<ml.get_y()<<" ";
        ss <<"L "<<tl.get_x()<<" "<<tl.get_y()<<" ";
        ss<<"L "<<tr.get_x()<<" "<<tr.get_y()<<" ";
        ss <<"L "<<mr.get_x()<<" "<<mr.get_y()<<" ";
        ss<<"L "<<br.get_x()<<" "<<br.get_y()<<" ";
        ss<<"z";
        return ss.str();
    }
}