#include <QtTest/QtTest>

#include <QColor>
#include <QImage>
#include <QPalette>

#include "pointswidget.h"
#include "mypoint.h"

class TestPointsWidget : public QObject
{
    Q_OBJECT

private slots:
    void constructor_initialState_isEmpty();
    void addPoint_storesPointAndIncreasesCount();
    void clearPoints_removesAllPoints();
    void clearPoints_whenAlreadyEmpty_remainsEmpty();
    void render_afterAddingPoint_drawsPointWithExpectedColor();
};

void TestPointsWidget::constructor_initialState_isEmpty()
{
    PointsWidget widget;

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

void TestPointsWidget::addPoint_storesPointAndIncreasesCount()
{
    PointsWidget widget;

    const MyPoint first(QPoint(3, 10), Qt::red);
    const MyPoint second(QPoint(7, 20), Qt::blue);

    widget.addPoint(first);
    widget.addPoint(second);

    QCOMPARE(widget.pointCount(), 2);
    QCOMPARE(widget.points().size(), 2);
    QCOMPARE(widget.points().at(0), first);
    QCOMPARE(widget.points().at(1), second);
}

void TestPointsWidget::clearPoints_removesAllPoints()
{
    PointsWidget widget;

    widget.addPoint(MyPoint(QPoint(1, 5), Qt::red));
    widget.addPoint(MyPoint(QPoint(2, 6), Qt::green));
    QCOMPARE(widget.pointCount(), 2);

    widget.clearPoints();

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

void TestPointsWidget::clearPoints_whenAlreadyEmpty_remainsEmpty()
{
    PointsWidget widget;

    widget.clearPoints();

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

void TestPointsWidget::render_afterAddingPoint_drawsPointWithExpectedColor()
{
    PointsWidget widget;
    widget.resize(20, 20);

    QPalette palette = widget.palette();
    palette.setBrush(QPalette::Base, QBrush(Qt::white));
    widget.setPalette(palette);

    widget.addPoint(MyPoint(QPoint(5, 7), Qt::red));

    QImage image(widget.size(), QImage::Format_ARGB32);
    image.fill(Qt::black);

    widget.render(&image);

    QCOMPARE(image.pixelColor(5, 7), QColor(Qt::red));

    QCOMPARE(image.pixelColor(0, 0), QColor(Qt::white));
    QCOMPARE(image.pixelColor(15, 15), QColor(Qt::white));
}

QTEST_MAIN(TestPointsWidget)
#include "test_pointswidget.moc"
