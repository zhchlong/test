//
// Created by l'l on 2022/5/26.
//

#include "arrowUp.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ArrowUp::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("arrow_up");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -90, 80);
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点

        ControlUp = createCorePoint("ControlUp",getX()+getWidth()/4,getY()+getHeight()/2);
        ControlDown = createCorePoint("ControlDown",getX()+getWidth()/2,getY()+getHeight());
        ControlUp->setColor("orange");
        ControlDown->setColor("orange");

        ControlDown->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(ny < getY()){
                ControlDown->setY(getY());
            }
            if(ny > getY()+getHeight()){
                ControlDown->setY(getY()+getHeight());
            }
        });

        ControlUp->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if(nx < getX()){
                ControlUp->setX(getX());
            }
            if(nx > getX()+getWidth()/2){
                ControlUp->setX(getX()+getWidth()/2);
            }
            if(ny > getY()+getHeight()){
                ControlUp->setY(getY()+getHeight());
            }
            if(ny < getY()){
                ControlUp->setY(getY());
            }
        });
        setCorePoints({ControlUp,ControlDown});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ArrowUp::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &ArrowUp::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const ArrowUp &>(comp);
        // 拷贝关键点位置
        *ControlUp = *(p.ControlUp);
        *ControlDown = *(p.ControlDown);

        return *this;
    }
    // 序列化，并记录已操作的
    void ArrowUp::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &ArrowUp::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        ControlUp = corePoints["ControlUp"];
        ControlDown = corePoints["ControlDown"];

        return *this;
    }

    //// Basics虚接口
    void ArrowUp::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        double dux = ControlUp->getX() - getX();
        double duy = ControlUp->getY() - getY();

        double ddy = getY()+getHeight() - ControlDown->getY();
        if(id == "ControlUp"){
            corePointMoving = true; // 开启更新锁
            *ControlUp += createPoint(dx,dy);
            corePointMoving = false;
        }
        else if(id == "ControlDown"){
            corePointMoving = true; // 开启更新锁
            *ControlDown += createPoint(0,dy);
            corePointMoving = false;
        }
        else{
            Rectangle::moveCorePoint(id, dx, dy);
            if(ddy > getHeight()){
                ddy = getHeight();
            }
            *ControlDown = createPoint(getX()+getWidth()/2,getY()+getHeight()-ddy);

            if(dux > getWidth()/2){
                dux = getWidth()/2;
            }
            if(duy > getHeight()){
                duy = getHeight();
            }
            *ControlUp = createPoint(getX()+dux,getY()+duy);
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string ArrowUp::getPath() const {



        auto ld = createPoint(ControlUp->getX(),getY()+getHeight());
        auto lm = createPoint(getX(),ControlUp->getY());
        auto lu = createPoint(getX()+getWidth()/2,getY());
        auto rm = createPoint(getX()+getWidth(),ControlUp->getY());
        auto rc = createPoint(2*ControlDown->getX()-ControlUp->getX(),ControlUp->getY());
        auto rd = createPoint(rc.get_x(),getY()+getHeight());




        std::stringstream ss;
        ss << "M " << ControlDown->getX() << " " << ControlDown->getY() << " ";
        ss << "L " << ld.get_x() << " " << ld.get_y() << " ";
        ss << "L " << ControlUp->getX() << " " << ControlUp->getY() << " ";
        ss << "L " << lm.get_x() << " " << lm.get_y() << " ";
        ss << "L " << lu.get_x() << " " << lu.get_y() << " ";
        ss << "L " << rm.get_x() << " " << rm.get_y() << " ";
        ss << "L " << rc.get_x() << " " << rc.get_y() << " ";
        ss << "L " << rd.get_x() << " " << rd.get_y() << " ";
        ss << "Z";

        return ss.str();
    }
}