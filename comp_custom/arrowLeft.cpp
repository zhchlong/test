//
// Created by l'l on 2022/5/26.
//

#include "arrowLeft.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ArrowLeft::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("arrow_left");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -20, 10);


        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点

        ControlLeft = createCorePoint("ControlLeft",getX()+getWidth()/2,getY()+getHeight()/4);
        ControlRight = createCorePoint("ControlRight",getX()+getWidth(),getY()+getHeight()/2);
        ControlLeft->setColor("orange");
        ControlRight->setColor("orange");

        ControlRight->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()){
                ControlRight->setX(getX());
            }
            if(nx > getX()+getWidth()){
                ControlRight->setX(getX()+getWidth());
            }
        });

        ControlLeft->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()){
                ControlLeft->setX(getX());
            }
            if(nx > getX()+getWidth()){
                ControlLeft->setX(getX()+getWidth());
            }
            if(ny > getY()+getHeight()/2){
                ControlLeft->setY(getY()+getHeight()/2);
            }
            if(ny < getY()){
                ControlLeft->setY(getY());
            }
        });
        setCorePoints({ControlLeft,ControlRight});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ArrowLeft::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &ArrowLeft::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const ArrowLeft &>(comp);
        // 拷贝关键点位置
        *ControlLeft = *(p.ControlLeft);
        *ControlRight = *(p.ControlRight);

        return *this;
    }
    // 序列化，并记录已操作的
    void ArrowLeft::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &ArrowLeft::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        ControlLeft = corePoints["ControlLeft"];
        ControlRight = corePoints["ControlRight"];

        return *this;
    }

    //// Basics虚接口
    void ArrowLeft::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        double dlx = ControlLeft->getX() - getX();
        double dly = ControlLeft->getY() - getY();
        double drx = getX()+getWidth() - ControlRight->getX();
        if(id == "ControlLeft"){
            corePointMoving = true; // 开启更新锁
            *ControlLeft += createPoint(dx,dy);
            corePointMoving = false;
        }
        else if(id == "ControlRight"){
            corePointMoving = true; // 开启更新锁
            *ControlRight += createPoint(dx,0);
            corePointMoving = false;
        }
        else{
            Rectangle::moveCorePoint(id, dx, dy);

            if(dlx > getWidth()){
                dlx = getWidth();
            }
            if(dly > getHeight()/2){
                dly = getHeight()/2;
            }
            *ControlLeft = createPoint(getX()+dlx,getY()+dly);

            if(drx > getWidth()){
                drx = getWidth();
            }
            *ControlRight = createPoint(getX()+getWidth() - drx,getY()+getHeight()/2);
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string ArrowLeft::getPath() const {


        auto tl = createPoint(getX(),getY()+getHeight()/2);
        auto tm = createPoint(ControlLeft->getX(),getY());
        auto tr = createPoint(getX()+getWidth(),ControlLeft->getY());
        auto br = createPoint(getX()+getWidth(),2*ControlRight->getY()-tr.get_y());
        auto bc = createPoint(ControlLeft->getX(),2*ControlRight->getY()-ControlLeft->getY());
        auto bm = createPoint(ControlLeft->getX(),getY()+getHeight());


        std::stringstream ss;
        ss << "M " << ControlRight->getX() << " " << ControlRight->getY() << " ";
        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";
        ss << "L " << ControlLeft->getX() << " " << ControlLeft->getY() << " ";
        ss << "L " << tm.get_x() << " " << tm.get_y() << " ";
        ss << "L " << tl.get_x() << " " << tl.get_y() << " ";
        ss << "L " << bm.get_x() << " " << bm.get_y() << " ";
        ss << "L " << bc.get_x() << " " << bc.get_y() << " ";
        ss << "L " << br.get_x() << " " << br.get_y() << " ";
        ss << "Z";

        return ss.str();
    }
}