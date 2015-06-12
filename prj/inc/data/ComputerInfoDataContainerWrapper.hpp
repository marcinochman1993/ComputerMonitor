/*
 * ComputerInfoDataContainerWrapper.hpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFODATACONTAINERWRAPPER_HPP_
#define COMPUTERINFODATACONTAINERWRAPPER_HPP_

#include <QObject>
#include "ComputerInfoDataContainer.hpp"

/*!
 * \brief Klasa pośrednicząca pomiędzy kontrolkami Qt a biblioteką SystemMonitoringLib
 *
 * Umożliwia za pomocą sygnałów informowanie o aktualizacji danych komputera
 */
class ComputerInfoDataContainerWrapper: public QObject, public Info
{
    Q_OBJECT

  public:
    /*!
     * \brief Konstruktor klasy ComputerInfoDataContainerWrapper
     *
     * Ustawia kontener przchowujący dane o komputerze na nullptr
     */
    ComputerInfoDataContainerWrapper():QObject(nullptr), m_dataContainer(nullptr) { }

    /*!
     * \brief Pozwala ustawić kontener przechowujący dane o komputerze
     *
     * \param dataContainer - wskaźnik na kontener przechowujący dane
     */
    void data(ComputerInfoDataContainer* dataContainer) { m_dataContainer = dataContainer; }

    /*!
     * \return Zwraca wskaźnik na kontener przechowujący dane
     */
    const ComputerInfoDataContainer* dataContainer() const { return m_dataContainer; }

    public slots:
    /*!
     * \brief Umożliwia aktualizację informacji o komputerze
     */
    bool update();

    /*!
     * \brief Metoda pozwalająca zaktualizować informacje o komputerze z łańcucha znaków
     *
     * \param strFromNet - łańcuch znaków na podstawie którego zostaną zaktualizowane informacje
     * \return Zwraca true jeśli aktualizacja się powiedzie, w.p.p. false
     */
    bool update(const std::string& strFromNet);

    /*!
     * \brief Metoda pozwala wyczyścić dane o komputerze.
     *
     * Usuwane są wszystkie informacje, które były do tej pory przetrzymywane o komputerze.
     */
    void clear();

  private:

    /*!
     * \brief Pole przechowujące wskaźnik na kontener zasobów danych o komputerze
     */
    ComputerInfoDataContainer* m_dataContainer;

  signals:
  /*!
   * \brief Sygnał oznaczający aktualizację danych
   *
   * Jest on generowany po tym, jak dane o komputerze
   * zostaną zaktualizowane
   */
    void dataUpdated();
};

#endif /* COMPUTERINFODATACONTAINERWRAPPER_HPP_ */
