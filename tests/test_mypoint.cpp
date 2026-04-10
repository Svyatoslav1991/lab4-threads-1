#include <QtTest/QtTest>

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPoint>

#include "mypoint.h"

class TestMyPoint : public QObject
{
    Q_OBJECT

private slots:
    void defaultConstructor_initializesOriginAndBlackColor();
    void constructor_storesPointAndColor();
    void equalityOperator_comparesPointAndColor();
    void draw_drawsVerticalLineWithExpectedColor();
};

void TestMyPoint::defaultConstructor_initializesOriginAndBlackColor()
{
    const MyPoint point;

    QCOMPARE(point.point(), QPoint(0, 0));
    QCOMPARE(point.color(), QColor(Qt::black));
}

void TestMyPoint::constructor_storesPointAndColor()
{
    const MyPoint point(QPoint(10, 20), Qt::red);

    QCOMPARE(point.point(), QPoint(10, 20));
    QCOMPARE(point.color(), QColor(Qt::red));
}

void TestMyPoint::equalityOperator_comparesPointAndColor()
{
    const MyPoint first(QPoint(3, 7), Qt::blue);
    const MyPoint second(QPoint(3, 7), Qt::blue);
    const MyPoint third(QPoint(4, 7), Qt::blue);
    const MyPoint fourth(QPoint(3, 7), Qt::green);

    QVERIFY(first == second);
    QVERIFY(first != third);
    QVERIFY(first != fourth);
}

void TestMyPoint::draw_drawsVerticalLineWithExpectedColor()
{
    QImage image(20, 20, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    const MyPoint point(QPoint(5, 7), Qt::red);
    point.draw(painter);
    painter.end();

    for (int y = 7; y < image.height(); ++y) {
        QCOMPARE(image.pixelColor(5, y), QColor(Qt::red));
    }

    QCOMPARE(image.pixelColor(4, 7), QColor(Qt::white));
    QCOMPARE(image.pixelColor(6, 7), QColor(Qt::white));
}

QTEST_MAIN(TestMyPoint)
#include "test_mypoint.moc"
