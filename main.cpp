#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSpacerItem>
#include <QShortcut>
#include <QKeySequence>
#include <QPainter>

//槽函数声明
void on_saveButton_clicked();
void on_cancelButton_clicked(QWidget*);
void on_clearButton_clicked(QLineEdit*);

//自定义一个按钮类型,设置这个按钮类型的颜色
class GradientButton : public QPushButton
{
public:
    GradientButton(const QString &text, QWidget *parent = nullptr) : QPushButton(text, parent){}

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setOpacity(1); //设置透明度

        QLinearGradient gradient(0,0,width(),height());
        gradient.setColorAt(0,QColor(37,96,26));
        gradient.setColorAt(1,QColor(184,229,186));

        painter.fillRect(rect(),gradient);
        painter.drawText(rect(),Qt::AlignCenter,text());
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    //创建控件
    QLabel *nameLabel = new QLabel("姓名(N)");
    //快捷键设置
    QLineEdit *nameLineEdit = new QLineEdit;
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N),&w);
    //将快捷键与信号关联
    QObject::connect(shortcut,&QShortcut::activated,nameLineEdit,[nameLineEdit](){
        nameLineEdit->setFocus();
    });

    QLabel *numLabel = new QLabel("学号:");
    QLabel *num = new QLabel("52240209");

    QLabel *ageLabel = new QLabel("年龄(A)");
    QSpinBox *ageSpinBox = new QSpinBox;
    ageSpinBox->setRange(15,25);
    //快捷键设置
    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_A),&w);
    //将快捷键与信号关联
    QObject::connect(shortcut1,&QShortcut::activated,ageSpinBox,[ageSpinBox](){
        ageSpinBox->setFocus();
    });

    QLabel *acadeLabel = new QLabel("所属院系");
    QComboBox *acadeComboBox = new QComboBox;
    acadeComboBox->addItem("信息工程学院");
    acadeComboBox->addItem("机械工程学院");
    acadeComboBox->addItem("电器工程学院");

    QGroupBox *genderGroupBox = new QGroupBox("性别");
    QRadioButton *maleRadioButton = new QRadioButton("男");
    QRadioButton *femaleRadioButton = new QRadioButton("女");

    QGroupBox *curriculumGroupBox = new QGroupBox("选修课程");
    QCheckBox *musicCheckBox = new QCheckBox("音乐鉴赏");
    QCheckBox *yogaCheckBox = new QCheckBox("瑜伽健身");

    GradientButton *saveButton = new GradientButton("保存");
    GradientButton *cancelButton = new GradientButton("取消");
    GradientButton *clearButton = new GradientButton("清空");

    QObject::connect(saveButton,&QPushButton::clicked,&on_saveButton_clicked);
    QObject::connect(cancelButton,&QPushButton::clicked,[&w](){
        on_cancelButton_clicked(&w);
    });
    QObject::connect(clearButton,&QPushButton::clicked,[nameLineEdit](){
        on_clearButton_clicked(nameLineEdit);
    });

    //设置控件的Tab顺序
    QWidget::setTabOrder(nameLineEdit,ageSpinBox);
    QWidget::setTabOrder(ageSpinBox,acadeComboBox);
    QWidget::setTabOrder(acadeComboBox,maleRadioButton);
    QWidget::setTabOrder(maleRadioButton,femaleRadioButton);
    QWidget::setTabOrder(femaleRadioButton,musicCheckBox);
    QWidget::setTabOrder(musicCheckBox,yogaCheckBox);
    QWidget::setTabOrder(yogaCheckBox,saveButton);
    QWidget::setTabOrder(saveButton,cancelButton);
    QWidget::setTabOrder(cancelButton,clearButton);


    /*--------------------------------------------------------------------------------------*/

    //控件布局
    QVBoxLayout *mainLayout = new QVBoxLayout(&w);

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    QHBoxLayout *parallelLayout1 = new QHBoxLayout;

    QHBoxLayout *numLayout = new QHBoxLayout;
    numLayout->addWidget(numLabel);
    numLayout->addWidget(num);

    QHBoxLayout *ageLayout = new QHBoxLayout;
    ageLayout->addWidget(ageLabel);
    ageLayout->addWidget(ageSpinBox);

    parallelLayout1->addLayout(numLayout);
    parallelLayout1->addLayout(ageLayout);

    QHBoxLayout *acadeLayout = new QHBoxLayout;
    acadeLayout->addWidget(acadeLabel);
    acadeLayout->addWidget(acadeComboBox);

    QHBoxLayout *parallelLayout2 = new QHBoxLayout;

    QVBoxLayout *genderLayout = new QVBoxLayout;
    genderLayout->addWidget(maleRadioButton);
    genderLayout->addWidget(femaleRadioButton);
    genderGroupBox->setLayout(genderLayout);
    genderGroupBox->setMinimumSize(150,100);
    genderGroupBox->setMaximumSize(200,150);

    QVBoxLayout *curriculumLayout = new QVBoxLayout;
    curriculumLayout->addWidget(musicCheckBox);
    curriculumLayout->addWidget(yogaCheckBox);
    curriculumGroupBox->setLayout(curriculumLayout);
    curriculumGroupBox->setMinimumSize(100,75);
    curriculumGroupBox->setMaximumSize(200,150);

    parallelLayout2->addWidget(genderGroupBox);
    //创建一个弹簧
    QSpacerItem *spacer = new QSpacerItem(20,10,QSizePolicy::Minimum,QSizePolicy::Minimum);
    parallelLayout2->addItem(spacer);
    parallelLayout2->addWidget(curriculumGroupBox);
    //设置布局固定大小
    parallelLayout2->setSizeConstraint(QLayout::SetFixedSize);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(clearButton);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(parallelLayout1);
    mainLayout->addLayout(acadeLayout);
    mainLayout->addLayout(parallelLayout2);
    mainLayout->addLayout(buttonLayout);

    /*--------------------------------------------------------------------------------------*/

    //显示控件
    w.resize(400,300);
    w.show();
    return a.exec();
}

void on_saveButton_clicked()
{
    QMessageBox::information(nullptr,"提示","肖浪保存成功!");
}

void on_cancelButton_clicked(QWidget* widget)
{
    widget->close();
}

void on_clearButton_clicked(QLineEdit* l)
{
    l->clear();
}
