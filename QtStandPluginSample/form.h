#ifndef FORM_H
#define FORM_H

#include <QLabel>
#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

public slots:
    void on_pushButtonExperiment_clicked();

public:
    QLabel *getLabel() const; // Because all GUI controls are located in private section some getter func is needed

signals:
    void OnSendingSignal(int value); // sending signal to model class

private:
    Ui::Form *ui;
};

#endif // FORM_H
