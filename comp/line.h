//
// Created by l'l on 2022/5/16.
//

#ifndef WEBSOCKETSERVER_LINE_H
#define WEBSOCKETSERVER_LINE_H

#include "../comp_module.h"
#include <map>
#include <set>

namespace LewzenServer {
    class Line : virtual public ComponentRotatable,
                 virtual public ComponentScalable,
                 virtual public ComponentFlippable,
                 virtual public ComponentStylized {

    private:
        static bool registered;
        const std::string module_type = "Line";



    protected:

        // 注册接口
        void registering();

    public:
        const std::string &getLineType() const;

        void set_line_type(std::string lt);

    protected:
        std::string lineType="null" ;
    public:
        double getOffset() const;

        void setOffset(double offset);

    protected:
        std::string dotType="solid" ;

        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGILine;
        std::shared_ptr<Lewzen::SVGIPath> SVGICurve;
        std::shared_ptr<Lewzen::SVGIPath> SVGIVerticalLine;
        std::shared_ptr<Lewzen::SVGIPath> SVGIHorizontalLine;
        std::shared_ptr<Lewzen::SVGIPath> SVGICurveTwo;
        std::shared_ptr<Lewzen::SVGIPath> SVGIHallowLine;
        std::shared_ptr<Lewzen::SVGIPath> SVGIComplexLine;
        std::shared_ptr<Lewzen::SVGIPath> SVGIFlexableLine;

        //hidden SVGI

        std::shared_ptr<Lewzen::SVGIPath> SVGILineHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGICurveHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGIVerticalLineHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGIHorizontalLineHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGICurveTwoHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGIHallowLineHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGIComplexLineHide;
        std::shared_ptr<Lewzen::SVGIPath> SVGIFlexableLineHide;

        // 关键点序列,顺序
        std::vector<std::shared_ptr<CorePoint> > pointList;

        //线条起点
        std::shared_ptr<CorePoint> startPoint;
        //线条终点
        std::shared_ptr<CorePoint> endPoint;

        std::shared_ptr<CorePoint> midPoint;

        std::shared_ptr<CorePoint> midCPoint;
        std::shared_ptr<CorePoint> arrowPoint;
        std::shared_ptr<CorePoint> arrowCPoint;


        std::string startArrow = "null", endArrow = "null";

        std::string straightLine = "straight_line";
        std::string verticalLine = "vertical_line";
        std::string curve = "curve";
        std::string horizontalLine = "horizontal_line";
        std::string curveTwo = "curve_two";
        std::string hallowLine = "hallow_line";
        std::string complexLine = "complex_line";
        std::string flexableLine = "flexible_line";

        double offset = 0;

        std::map<std::string, std::shared_ptr<Lewzen::SVGIMarker>> arrows;


    protected:
        std::shared_ptr<Lewzen::SVGIMarker> end_arrow;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow;
        std::shared_ptr<Lewzen::SVGIPath> arrowPath;

        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_circle;
        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_circle;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_tri;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_tri;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_line;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_line;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_tri_h;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_tri_h;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_vline;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_vline;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_tri_half;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_tri_half;

        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_two_tri;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_two_tri;

        std::shared_ptr<Lewzen::SVGIMarker> hallow_line_arrow;


        int ndSize = 0;


    public:

        Line();

        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;

        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;

        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;

        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        virtual Lewzen::Point2D getRotateCenter() const;


        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// Scalable接口
        virtual void scale(const double &scaleX, const double &scaleY) override;

        //// Flippable接口
        virtual void flip(const double &a, const double &b, const double &c) override;

        //// 线条接口
        const CorePoint &getStartPoint() const;

        void setLineType(std::string lineType);

        void setStartPoint(const CorePoint &startPoint);

        const CorePoint &getEndPoint() const;

        void setEndPoint(const CorePoint &endPoint);

        std::string getD();

        void initArrow();

        const std::string &getStartArrow() const;

        virtual void setStartArrow(const std::string &startArrow);

        const std::string &getEndArrow() const;

        virtual void setEndArrow(const std::string &endArrow);

        std::string getCurveD();

        std::string getVerticalLineD();

        std::string getHorizontalLineD();

        std::string getCurveTwoD();

        std::string getHallowLineD();

        std::string getComplexLineD();

        std::string getFlexableLineD();

        Lewzen::Point2D getFlipPoint(Lewzen::Point2D p);

        Lewzen::Point2D getFlipP(Lewzen::Point2D p,Lewzen::Point2D s,Lewzen::Point2D e);

        const std::string &getDotType() const;

        void calcComplexPoint(double ew,double eh,double eh1,double sw,double sh,double sh1);

        void calcFlexablePoint(double ew,double eh,double eh1,double sw,double sh,double sh1);

        std::vector<Lewzen::Point2D> offsetCoords(std::vector<Lewzen::Point2D> coords, double offset);


        void onOffset();

        void closeOffset();

        double dist2d(Lewzen::Point2D coord1, Lewzen::Point2D coord2);

        void onSameSide();//将midC,arrowC调整到线段(start,end)同侧

        void onSameSideF();

        void setDotLine(std::string dotType);
    };
}


#endif //WEBSOCKETSERVER_LINE_H
