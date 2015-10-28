#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QDialog>

namespace Ui {
class DiagramWindow;
}

class DiagramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DiagramWindow(QWidget *parent = 0);
    ~DiagramWindow();

private:
    Ui::DiagramWindow *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // DIAGRAMWINDOW_H
