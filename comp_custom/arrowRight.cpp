//
// Created by l'l on 2022/5/26.
//

#include "arrowRight.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ArrowRight::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("arrow_right");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -20, 10);
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点

        ControlLeft = createCorePoint("ControlLeft",getX(),getY()+getHeight()/2);
        ControlRight = createCorePoint("ControlRight",getX()+getWidth()/2,getY()+getHeight()/4);
        ControlLeft->setColor("orange");
        ControlRight->setColor("orange");

        ControlLeft->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()){
                ControlLeft->setX(getX());
            }
            if(nx > getX()+getWidth()){
                ControlLeft->setX(getX()+getWidth());
            }
        });

        ControlRight->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()){
                ControlRight->setX(getX());
            }
            if(nx > getX()+getWidth()){
                ControlRight->setX(getX()+getWidth());
            }
            if(ny > getY()+getHeight()/2){
                ControlRight->setY(getY()+getHeight()/2);
            }
            if(ny < getY()){
                ControlRight->setY(getY());
            }
        });
        setCorePoints({ControlLeft,ControlRight});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ArrowRight::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &ArrowRight::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const ArrowRight &>(comp);
        // 拷贝关键点位置
        *ControlLeft = *(p.ControlLeft);
        *ControlRight = *(p.ControlRight);

        return *this;
    }
    // 序列化，并记录已操作的
    void ArrowRight::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &ArrowRight::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        ControlLeft = corePoints["ControlLeft"];
        ControlRight = corePoints["ControlRight"];

        return *this;
    }

    //// Basics虚接口
    void ArrowRight::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        double dl = ControlLeft->getX() - getX();
        double drx = getX()+getWidth() - ControlRight->getX();
        double dry = ControlRight->getY() - getY();
        if(id == "ControlLeft"){
            corePointMoving = true; // 开启更新锁
            *ControlLeft += createPoint(dx,0);
            corePointMoving = false;
        }
        else if(id == "ControlRight"){
            corePointMoving = true; // 开启更新锁
            *ControlRight += createPoint(dx,dy);
            corePointMoving = false;
        }
        else{
            Rectangle::moveCorePoint(id, dx, dy);
            if(dl > getWidth()){
                dl = getWidth();
            }
            *ControlLeft = createPoint(getX()+dl,getY()+getHeight()/2);

            if(drx > getWidth()){
                drx = getWidth();
            }
            if(dry > getHeight()/2){
                dry = getHeight()/2;
            }
            *ControlRight = createPoint(getX()+getWidth() - drx,getY()+dry);
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string ArrowRight::getPath() const {


        auto tl = createPoint(getX(), ControlRight->getY());
        auto tm = createPoint(ControlRight->getX(), getY());
        auto tr = createPoint(getX() + getWidth(), getY() + getHeight() / 2);
        auto bl = createPoint(tl.get_x(), 2 * ControlLeft->getY() - tl.get_y());
        auto bc = createPoint(ControlRight->getX(), 2 * ControlLeft->getY() - ControlRight->getY());
        auto bm = createPoint(ControlRight->getX(), getY() + getHeight());

        std::stringstream ss;
        ss << "M " << ControlLeft->getX() << " " << ControlLeft->getY() << " ";
        ss << "L " << tl.get_x() << " " << tl.get_y() << " ";
        ss << "L " << ControlRight->getX() << " " << ControlRight->getY() << " ";
        ss << "L " << tm.get_x() << " " << tm.get_y() << " ";
        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";
        ss << "L " << bm.get_x() << " " << bm.get_y() << " ";
        ss << "L " << bc.get_x() << " " << bc.get_y() << " ";
        ss << "L " << bl.get_x() << " " << bl.get_y() << " ";
        ss << "Z";

        return ss.str();
    }
}