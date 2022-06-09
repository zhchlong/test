//
// Created by l'l on 2022/5/29.
//

#include "package.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Package::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("package");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形

        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点
        Control = createCorePoint("Control", getX()+getWidth()/2,getY()+padding);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (nx > getX() + getWidth()) {
                Control->setX(getX() + getWidth()); // 不允许超过宽度的1/4
            }

            if (nx < getX()) {
                Control->setX(getX()); // 不允许低于矩形的X坐标
            }

            if(ny > getY()+getHeight()){
                Control->setY(getY()+getHeight());
            }

            if(ny < getY()){
                Control->setY(getY());
            }
        });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Package::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &Package::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Package &>(comp);
        // 拷贝关键点位置
        *Control = *(p.Control);

        return *this;
    }
    // 序列化，并记录已操作的
    void Package::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Package::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        Control = corePoints["Control"];

        return *this;
    }

    //// Basics虚接口
    void Package::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double d = Control->getX() - getX(); // 记录控制点到矩形左边的距离
        double d1 = Control->getY() - getY();
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, dy); // 只允许横向移动
            corePointMoving = false;
        } else { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            // 更新控制点
            if (d > getWidth()) {
                d = getWidth() ; // 不允许超过宽度的1/4
            }
            if(d1 > getHeight()){
                d1 = getHeight();
            }
            *Control = createPoint(getX()+d, getY()+d1); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string Package::getPath() const {


        auto tl = createPoint(getX(),getY());
        auto tm = createPoint(Control->getX(),getY());

        auto ml = createPoint(getX(),Control->getY());
        auto mr = createPoint(getX()+getWidth(),Control->getY());

        auto dl = createPoint(getX(),getY()+getHeight());
        auto dm = createPoint(getX()+getWidth()/2,getY()+getHeight());
        auto dr = createPoint(getX()+getWidth(),getY()+getHeight());

        std::stringstream ss;

        ss << "M " << ml.get_x()<<" "<<ml.get_y()<<" ";
        ss <<"L "<<tl.get_x()<<" "<<tl.get_y()<<" ";
        ss<<"L "<<tm.get_x()<<" "<<tm.get_y()<<" ";
        ss<<"L "<<Control->getX()<<" "<<Control->getY()<<" ";
        ss << "M " << ml.get_x()<<" "<<ml.get_y()<<" ";
        ss<<"L "<<mr.get_x()<<" "<<mr.get_y()<<" ";
        ss<<"L "<<dr.get_x()<<" "<<dr.get_y()<<" ";
        ss<<"L "<<dl.get_x()<<" "<<dl.get_y()<<" ";

        ss<<"z";
        return ss.str();
    }
}