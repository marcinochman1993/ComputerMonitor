/*
 * RadialIndicator.hpp
 *
 *  Created on: May 19, 2015
 *      Author: mochman
 */

#ifndef RADIALINDICATOR_HPP_
#define RADIALINDICATOR_HPP_

#include <QWidget>
#include <QPropertyAnimation>

/*!
 * \brief Klasa reprezentująca okrągły, analogowy wskaźnik prezentujący dane w procentach
 */
class RadialIndicator: public QWidget
{
    Q_OBJECT

  public:
    /*!
     * \brief Konstruktor klasy RadialIndicator
     *
     * Domyślnie wartość jest ustawiona na 0% tj. -45 stopni
     *
     * \param parent - rodzic kontrolki
     */
    RadialIndicator(QWidget* parent = nullptr): QWidget(parent), m_angle(-45.0) { init(); }

    /*!
     * \brief Metoda rysująca kontrolkę
     * \param event - informacje o zdarzeniu
     */
    void paintEvent(QPaintEvent * event) override;

    /*!
     * \brief Metoda ustawia nową wartość procentową
     *
     * Po jej ustawieniu następuje animacja kontrolki
     *
     * \param newValue - nowa wartość procentowa
     */
    void setValuePercent(double newValue);

    /*!
     * \brief Metoda pozwalająca pobrać aktualną wartość procentową prezentowaną przez kontrolkę
     * \return Zwracana jest aktualna wartość procentową prezentowaną przez kontrolkę
     */
    double valuePercent() const { return m_valuePercent; }

  private:
    /*!
     * \brief Metoda pozwala pobrać kąt obrotu wskazówki
     * \return Zwracany jest kąt obrotu wskazówki wyrażony w stopniach
     */
    int getAngle() const { return m_angle; }

    /*!
     * \brief Metoda pozwala ustawić kąt obrotu wskazówki
     * \param newAngle - nowy kąt obrotu wskazówki
     */
    void setAngle(int newAngle ) { m_angle = newAngle; repaint(); }

    /*!
     * \brief Metoda inicjuje kontrolkę
     */
    void init();

    /*!
     * \brief Pole przechowujące wartość procentową prezentowaną przez kontrolkę
     */
    double m_valuePercent;

    /*!
     * \brief Pole przechowujące kąt obrotu wskazówki wyrażonego w procentach
     */
    int m_angle;

    /*!
     * \brief Pole przechowujące wskaźnik do zarządcy animacji wskazówki
     */
    QPropertyAnimation* m_propertyAnimation;

    Q_PROPERTY(int angle  READ getAngle WRITE setAngle)
};

#endif /* RADIALINDICATOR_HPP_ */
