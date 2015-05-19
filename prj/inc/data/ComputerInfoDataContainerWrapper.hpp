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

    /*!
     * \brief Umożliwia aktualizację informacji o komputerze
     */
    bool update();

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
