#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QContextMenuEvent>
#include <QColor>
#include <QInputDialog>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

//! [0]
class Node : public QGraphicsItem
{
   // Q_OBJECT
public:
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool gravity = false;
    char* name;
    GraphWidget *graph;
    QColor grad0 = Qt::white;
    QColor grad1 = Qt::gray;
    QList<Edge *> edgeList;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:

    QPointF newPos;


};
//! [0]

#endif // NODE_H
