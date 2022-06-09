//
// Created by l'l on 2022/5/26.
//


#include "arrowDown.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ArrowDown::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("arrow_down");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -90, 80);
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点

        ControlUp = createCorePoint("ControlUp",getX()+getWidth()/2,getY());
        ControlDown = createCorePoint("ControlDown",getX()+getWidth()*3/4,getY()+getHeight()/2);
        ControlUp->setColor("orange");
        ControlDown->setColor("orange");

        ControlUp->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(ny < getY()){
                ControlUp->setY(getY());
            }
            if(ny > getY()+getHeight()){
                ControlUp->setY(getY()+getHeight());
            }
        });

        ControlDown->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()+getWidth()/2){
                ControlDown->setX(getX()+getWidth()/2);
            }
            if(nx > getX()+getWidth()){
                ControlDown->setX(getX()+getWidth());
            }
            if(ny > getY()+getHeight()){
                ControlDown->setY(getY()+getHeight());
            }
            if(ny < getY()){
                ControlDown->setY(getY());
            }
        });
        setCorePoints({ControlUp,ControlDown});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ArrowDown::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &ArrowDown::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const ArrowDown &>(comp);
        // 拷贝关键点位置
        *ControlUp = *(p.ControlUp);
        *ControlDown = *(p.ControlDown);

        return *this;
    }
    // 序列化，并记录已操作的
    void ArrowDown::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);

    }
    // 反序列化
    ComponentAbstract &ArrowDown::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点

        ControlUp = corePoints["ControlUp"];
        ControlDown = corePoints["ControlDown"];

        return *this;
    }

    //// Basics虚接口
    void ArrowDown::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        double duy = ControlUp->getY() - getY();
        double ddy = getY()+getHeight() - ControlDown->getY();
        double ddx = getX()+getWidth() - ControlDown->getX();
        if(id == "ControlUp"){
            corePointMoving = true; // 开启更新锁
            *ControlUp += createPoint(0,dy);
            corePointMoving = false;
        }
        else if(id == "ControlDown"){
            corePointMoving = true; // 开启更新锁
            *ControlDown += createPoint(dy,dy);
            corePointMoving = false;
        }
        else{
            Rectangle::moveCorePoint(id, dx, dy);
            if(duy > getHeight()){
                duy = getHeight();
            }
            *ControlUp = createPoint(getX()+getWidth()/2,getY()+duy);

            if(ddx > getWidth()/2){
                ddx = getWidth()/2;
            }
            if(ddy > getHeight()){
                ddy = getHeight();
            }
            *ControlDown = createPoint(getX()+getWidth()-ddx,getY()+getHeight()-ddy);
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string ArrowDown::getPath() const {


        auto ld = createPoint(getX()+getWidth()/2,getY()+getHeight());
        auto lm = createPoint(getX(),ControlDown->getY());
        auto lc = createPoint(2*ControlUp->getX()-ControlDown->getX(),ControlDown->getY());
        auto lu = createPoint(lc.get_x(),getY());

        auto ru = createPoint(ControlDown->getX(),getY());
        auto rm = createPoint(getX()+getWidth(),ControlDown->getY());


        std::stringstream ss;
        ss << "M " << ControlDown->getX() << " " << ControlDown->getY() << " ";
        ss << "L " << rm.get_x() << " " << rm.get_y() << " ";
        ss << "L " << ld.get_x() << " " << ld.get_y() << " ";
        ss << "L " << lm.get_x() << " " << lm.get_y() << " ";
        ss << "L " << lc.get_x() << " " << lc.get_y() << " ";
        ss << "L " << lu.get_x() << " " << lu.get_y() << " ";
        ss << "L " << ControlUp->getX() << "," << ControlUp->getY() << " ";
        ss << "L " << ru.get_x() << " " << ru.get_y() << " ";
        ss << "Z";

        return ss.str();
    }
}
