#include <QPoint>
#include <QQuickItem>
#include <QString>
#include <QTimer>
#include <memory>
#include "book_controller.hpp"
#include "page_controller.hpp"
#include "presentation_export.hpp"

namespace cpp_elements
{

/**
 * This class is responsible for rendering a single page of the book.
 * It derives from QQuickItem, which is the base class for all visual item
 * types in Qml. It is a visual item that can be drawn on the screen and
 * interacted with.
 */
class PRESENTATION_EXPORT PageView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(adapters::controllers::BookController* bookController WRITE
                   setBookController CONSTANT)
    Q_PROPERTY(
        int implicitWidth READ getImplicitWidth NOTIFY implicitWidthChanged)
    Q_PROPERTY(
        int implicitHeight READ getImplicitHeight NOTIFY implicitHeightChanged)
    Q_PROPERTY(int pageNumber READ getPageNumber WRITE setPageNumber CONSTANT)
    Q_PROPERTY(bool colorInverted WRITE setColorInverted)


public:
    PageView();

    int getImplicitWidth() const;
    int getImplicitHeight() const;

    int getPageNumber() const;
    void setPageNumber(int newCurrentPage);
    void setColorInverted(bool newColorInverted);

    void setBookController(
        adapters::controllers::BookController* newBookController);

private slots:
    void updateZoom(float newZoom);

protected:
    void geometryChange(const QRectF& newGeometry,
                        const QRectF& oldGeometry) override;
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData* _) override;

    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void hoverMoveEvent(QHoverEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    void selectSingleWord();
    void selectMultipleWords();
    void selectLine();
    void copySelectedText();
    void removeSelection();
    void createSelection();
    void paintSelectionOnPage(QPainter& painter);

    void createHighlightFromCurrentSelection();
    void paintHighlightsOnPage(QPainter& painter);
    void removeConflictingHighlights(domain::entities::Highlight& highlight);
    bool mouseAboveSelection(const QPointF mouse);

    void resetCursorToDefault();
    void setCorrectCursor(int x, int y);

    std::unique_ptr<adapters::controllers::PageController> m_pageController;
    adapters::controllers::BookController* m_bookController = nullptr;
    int m_pageNumber = 0;
    bool m_firstTimeColorInverted = true;
    bool m_startedMousePressOnLink = false;
    QPointF m_selectionStart;
    QPointF m_selectionEnd;
    QTimer m_tripleClickTimer;
    bool m_doubleClickHold = false;
};

}  // namespace cpp_elements
