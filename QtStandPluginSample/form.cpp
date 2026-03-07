#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    // hadn't idea why Qt creator didn't connect the button slot func to the signal so I made it manually
    connect(ui->pushButtonExperiment, SIGNAL(clicked()), this, SLOT(on_pushButtonExperiment_clicked()));
}

Form::~Form()
{
    delete ui;
}

// getting access to the label control
QLabel *Form::getLabel() const
{
    return ui->label;
}

// send data to model class
void Form::on_pushButtonExperiment_clicked()
{
   emit OnSendingSignal(5555);
}
