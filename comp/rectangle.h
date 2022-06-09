#ifndef __LEWZENSERVER_RECTANGLE__
#define __LEWZENSERVER_RECTANGLE__

#include "../comp_module.h"

namespace LewzenServer {
    class Rectangle : virtual public ComponentRotatable,
                      virtual public ComponentScalable,
                      virtual public ComponentFlippable,
                      virtual public ComponentWritable,
                      virtual public ComponentStylized {
    private:
        static bool registered;
        const std::string module_type = "Rectangle";
    protected:
        // 注册接口
        void registering();
        // SVGI
        std::shared_ptr<Lewzen::SVGIRect> SVGIRect;
        // 关键点别名
        std::shared_ptr<CorePoint> LT, L, LB, B, RB, R, RT, T;
        // 标记
        bool corePointMoving = false;
    public:
        //// 基本接口
        // 构造
        Rectangle();

        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// Scalable接口
        virtual void scale(const double &scaleX, const double &scaleY) override;

        //// Flippable接口
        virtual void flip(const double &a, const double &b, const double &c) override;

        //// Writable虚接口
        virtual const ComponentWritable::WriteArea getWriteArea() override;

        //// 矩形接口
        virtual void resizeByChildren();
        virtual double getX() const;
        virtual double getY() const;
        virtual double getWidth() const;
        virtual double getHeight() const;
    };
}
#endif