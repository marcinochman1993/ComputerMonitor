/*
 * UsageDelegate.hpp
 *
 *  Created on: May 22, 2015
 *      Author: mochman
 */

#ifndef USAGEDELEGATE_HPP_
#define USAGEDELEGATE_HPP_

#include <QStyledItemDelegate>
#include <set>

/*!
 * \brief Jest to klasa reprezentująca delegat wykorzystania pewnego zasobu
 *
 * Delegat pokazuje w sposób graficzny wykorzystane zasoby w tabeli
 */
class UsageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy UsageDelegate
     *
     * \param parent - rodzic delegata, domyślnie brak
     */
    UsageDelegate(QWidget *parent = 0):QStyledItemDelegate(parent) { }

    /*!
     * \brief Metoda pozwalająca na rysowanie
     *
     * \param painter - obiekt, przy pomocy którego można rysować na ekranie
     * \param option - opcje dla rysowania informacji
     * \param index - indeks danych
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    /*!
     * \brief Pozwala dodać numer kolumny, która będzie prezentowana w sposób graficzny
     * \param column - numer kolumny, która ma być prezentowana przy pomocy paska gradientu w tabeli
     */
    void addColumnUsage(int column) { m_columnsUsage.insert(column); }

private:

    /*!
     * \brief Metoda określa gradient danego elementu
     *
     * Ze względu na procentowe wykorzystanie i obszat rysowania, określa
     * w jaki sposób zostanie narysowany gradient
     *
     * \param usagePercent - procentowe wykorzystanie
     * \param rect - obszar rysowania
     * \return Zwracany jest liniowy gradient, który zostanie narysowany na kontrolce.
     */
    QLinearGradient prepareGradient(double usagePercent, const QRect& rect) const;

    /*!
     * \brief Pole przechowujące numery kolumn w tabeli, które mają być prezentowane przy pomocy gradientu
     */
    std::set<int> m_columnsUsage;

};
#endif /* USAGEDELEGATE_HPP_ */
