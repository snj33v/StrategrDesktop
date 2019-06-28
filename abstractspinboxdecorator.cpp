#include "abstractspinboxdecorator.h"
#include <QtCore>
#include <QtWidgets>

int AbstractSpinBoxDecorator::getFontPixelSize() const { return fontPixelSize; }

void AbstractSpinBoxDecorator::setFontPixelSize(int value) {
  fontPixelSize = value;
  applyStyleSheet();
}

void AbstractSpinBoxDecorator::setup() {
  abstractSpinBox();
  createLayout();
  addSpinboxToLayout();
  createButtonsLayout();
  createButtonsWidget();

  applyStyleSheet();
}

void AbstractSpinBoxDecorator::applyStyleSheet() {
  setStyleSheet(QString("QAbstractSpinBox {"
                        "font-size: %1px;"
                        "border: none;"
                        "}"
                        "QAbstractSpinBox::up-button {"
                        "    width: 0px;"
                        "    height: 0px;"
                        "}"
                        "QAbstractSpinBox::up-arrow {"
                        "    width: 0px;"
                        "    height: 0px;"
                        "}"
                        "QAbstractSpinBox::down-button {"
                        "    width: 0px;"
                        "    height: 0px;"
                        "}"
                        "QAbstractSpinBox::down-arrow {"
                        "    width: 0px;"
                        "    height: 0px;"
                        "}")
                    .arg(QString::number(fontPixelSize)));
}

void AbstractSpinBoxDecorator::createLayout() {
  auto *mainLayout = new QHBoxLayout(this);
  mainLayout->setMargin(0);
  mainLayout->setSpacing(5);
  setLayout(mainLayout);
}

void AbstractSpinBoxDecorator::createButtonsLayout() {
  buttonsLayout = new QVBoxLayout();
  buttonsLayout->setContentsMargins(0, 0, 0, 0);
  buttonsLayout->setSpacing(0);
}

void AbstractSpinBoxDecorator::createButtonsWidget() {
  buttonsWidget = new QWidget(this);
  buttonsWidget->setLayout(buttonsLayout);
  buttonsWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  buttonsWidget->setMaximumHeight(2 * buttonsHeight);
  buttonsWidget->setMaximumWidth(buttonsWidth);

  layout()->addWidget(buttonsWidget);
  createButtons();
}

void AbstractSpinBoxDecorator::createButtons() {
  upButton = makeButton("\uf077");
  connect(upButton, &QPushButton::clicked, this,
          &AbstractSpinBoxDecorator::stepUp);

  downButton = makeButton("\uf078");
  connect(downButton, &QPushButton::clicked, this,
          &AbstractSpinBoxDecorator::stepDown);
}

void AbstractSpinBoxDecorator::addSpinboxToLayout() {
  layout()->addWidget(_abstractSpinBox);
}

QPushButton *AbstractSpinBoxDecorator::makeButton(QString text) {
  auto button = new QPushButton(this);
  button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  button->setMaximumHeight(buttonsHeight);
  button->setMaximumWidth(buttonsWidth);
  button->setFlat(true);
  button->setText(text);
  button->setStyleSheet("QPushButton {"
                        "border: none;"
                        "}"
                        "QPushButton:pressed {"
                        "color: #ccc;"
                        "}");

  QFont font;
  font.setFamily(fontResourcePath);
  font.setPixelSize(buttonsWidth / 2);

  button->setFont(font);

  buttonsLayout->addWidget(button);

  return button;
}

QAbstractSpinBox *AbstractSpinBoxDecorator::abstractSpinBox() const {}

AbstractSpinBoxDecorator::AbstractSpinBoxDecorator(QAbstractSpinBox *spinBox,
                                                   QWidget *parent)
    : QWidget(parent), _abstractSpinBox(spinBox) {
  spinBox->setParent(this);
  setup();
}

void AbstractSpinBoxDecorator::stepUp() {
  _abstractSpinBox->setFocus();
  _abstractSpinBox->stepUp();
}

void AbstractSpinBoxDecorator::stepDown() {
  _abstractSpinBox->setFocus();
  _abstractSpinBox->stepDown();
}
