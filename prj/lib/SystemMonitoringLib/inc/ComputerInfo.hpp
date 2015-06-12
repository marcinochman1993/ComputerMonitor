/*
 * ComputerInfo.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFO_HPP_
#define COMPUTERINFO_HPP_

#include "Info.hpp"
#include "SensorsVector.hpp"
#include "RamInfo.hpp"
#include "ProcessorInfo.hpp"
#include "AllProcessesInfo.hpp"
#include "ProcessorInfo.hpp"
#include "RamInfo.hpp"

/*!
 * \brief Klasa reprezentująca informacje o komputerze
 *
 * Klasa przechowuje informacje o komputerze
 */
class ComputerInfo: public Info
{
  public:


    /*!
     * \brief Struktura określająca parametry metody toString dla poszczególnych komponentów komputera
     */
    struct ToStringStruct
    {
      /*!
       * \brief Kontruktor struktury ToStringStruct
       *
       * Inicjuje wszystkie parametry na 0.
       */
      ToStringStruct(): processesFlags(0),processorFlags(0),ramFlags(0),sensorsFlags(0) { }

      /*!
       * \brief Pole określające parametry metody toString dla wszystkich procesów
       */
      int processesFlags;

      /*!
       * \brief Pole określające parametry metody toString dla procesora
       */
      int processorFlags;

      /*!
       * \brief Pole określające parametry metody toString dla pamięci RAM
       */
      int ramFlags;

      /*!
       * \brief Pole określające parametry metody toString dla wszystkich czujników
       */
      int sensorsFlags;
    };

    /*!
     * \brief Domyślny konstruktor klasy ComputerInfo
     *
     * Inicjuje podstawowe struktury przechowujące informacje o stanie komputera.
     */
    ComputerInfo(): m_initialized(false) { }

    /*!
     * \brief Pozwala na aktualizacje informacji o komputerze
     *
     * Aktualizuje wszystkie informacje o komputerze
     *
     * \return Zwraca true, jeśli wszystko się powiedzie. Jeśli pojawi się błąd zwróci false.
     */
    bool update() override;

    /*!
    * \brief Metoda aktualizuje informacje o komputerze na podstawie łańcucha znaków.
    *
    * \param strFromNet - łańuch znaków, na podstawie którego zostaną zaktualizowane dane
    * \return true jeśli aktualizacja się powiedzie, w.p.p false
    */
    bool update(const std::string& strFromNet);

    /*!
     * \brief Pozwala dostać się do zbioru wszystkich czujników
     *
     * \return Zwraca wektor czujników dostępnych na komputerze.
     */
    const SensorsVector& allSensors() const { return m_sensors; }

    /*!
     * \brief Pozwala dostać się do zbioru wszystkich procesów
     *
     * \return Zwraca zbiór procesów dostępnych na komputerze.
     */
    const AllProcessesInfo& allProcesses() const { return m_allProcesses; }

  /*!
   * \brief Metoda pozwalająca pobrać informacje o procesorze
   *
   * \return Zwracany jest obiekt przechowujący informacje o procesorze
   */
    const ProcessorInfo& processor() const { return m_processor; }

    /*!
     * \brief Metoda pozwalająca pobrać informacje o pamięci ram
     *
     * \return Zwracany jest obiekt przechowujący informacje o procesorze
     */
    const RamInfo& ram() const { return m_ram; }

    /*!
     * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący komputer.
     *
     * Generuje łańcuch znaków, w którym poszczególne komponenty są oddzielone znakiem nowej linii
     *
     * \param flags - parametr ignorowany
     * \return Łańcuch znaków opisujący informacje o komputerze.
     */
    std::string toString(unsigned flags = 0) const override;

    /*!
     * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący komputer.
     *
     * Generuje łańcuch znaków, w którym poszczególne komponenty są oddzielone znakiem nowej linii
     *
     * \param toStringParams - parametry dla metody opisujące, które elementy zostaną uwzględnione.
     * \return Łańcuch znaków opisujący informacje o komputerze.
     */
    std::string toString(const ToStringStruct& toStringParams) const;

    /*!
     * \brief Metoda pozwalająca usunąć wszelkie dostępne informacje o komputerze.
     *
     * Po wywołaniu metody, aby kolejny raz otrzymać informacje o komputerze należy
     * wywołać jedną z metod update.
     */
    void clear();

  private:
    /*!
     * \brief Pole przechowujące czujniki
     */
    SensorsVector m_sensors;

    /*!
     * \brief Pole przechowujące czujniki
     */
    AllProcessesInfo m_allProcesses;

    /*!
     * \brief Pole przechowujące informacje o procesorze
     */
    ProcessorInfo m_processor;

    /*!
     * \brief Pole przechowujące informacje o pamięci RAM
     */
    RamInfo m_ram;


    bool m_initialized;
};


#endif /* COMPUTERINFO_HPP_ */
