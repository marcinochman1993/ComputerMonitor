/*
 * ProcessesVector.hpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#ifndef PROCESSESVECTOR_HPP_
#define PROCESSESVECTOR_HPP_

#include "Info.hpp"
#include "ProcessInfo.hpp"
#include <map>
#include <vector>
/*!
 * \brief Kontener przechowujący informacje o wsyzstkich procesach
 */
class AllProcessesInfo: public Info
{
  public:
    /*!
     * \brief Konstruktor inicjujący proces
     *
     * Inicjuje proces o zadanym numerze id
     *
     * \param id - numer identyfikacyjny procesu
     */
    const ProcessInfo& process(unsigned int id) const;

    /*!
     * \brief Metoda pozwala sprawdzić czy w kontenerze znajduje się proces o podanym id
     *
     * \param id - numer identyfikacyjny procesu
     * \return Zwraca true jeśli w kontenerze znajduje się proces o podanym id
     */
    bool containsProcess(unsigned int id) const;

    /*!
     * \brief Metoda pozwala usunąć proces z kontenera
     *
     * \param id - numer identyfikacyjny procesu
     * \return Zwraca true jeśli w kontenerze znajdował się proces o podanym id i został usunięty
     */
    bool removeProcess(unsigned int id);

    /*!
     * \brief Metoda pozwala określić ilość procesów w systemie
     *
     * \return Zwracana jest ilość procesów w systemie
     */
    unsigned size() const { return m_processesMap.size(); }

    /*!
     * \brief Metoda pozwalająco zaktualizować informacje o wszystkich procesach
     *
     * Metoda aktualizuje informacje o procesach, które już były w kontenerze oraz
     * dodaje te które się pojawiły się w systemie
     *
     * \return true jeśli informacje o wszystkich procesach zostaną odczytane, w.p.p. false
     */
    bool update() override;

    /*!
     * \brief Metoda aktualizuje informacje o procesach na podstawie łańcucha znaków.
     *
     * \param strFromNet - łańcuch znaków, na podstawie którego zostaną zaktualizowane dane
     * \return true jeśli aktualizacja się powiedzie, w.p.p false
     */
    bool update(const std::string& strFromNet) override;

    /*!
     * \brief Metoda pozwala dostać kontener asocjacyjny, w którym przechowywane są procesy
     *
     * Opis kontenera znajduje się w \see m_processesMap
     *
     * \return Zwracany jest kontener asocjacyjny zawierający przechowywane procesy
     */
    const std::map<unsigned, ProcessInfo> processesMap() const { return m_processesMap; }

    /*!
     * \brief Metoda pozwalająca pobrać wektor ostatnio utworzonych procesów
     *
     * \return Zwracane są ostatnio utworzone procesy
     */
    const std::vector<unsigned> lastAddedProcesses() const { return m_lastAddedProcesses; }

    /*!
     * \brief Metoda pozwalająca pobrać wektor ostatnio usuniętych procesów
     *
     * \return Zwracane są ostatnio usunięte procesy
     */
    const std::vector<unsigned>& lastDeletedProcesses() const { return m_lastDeletedProcesses; }

    /*!
     * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący wszystkie procesy.
     *
     * Generuje łańuch znaków typu: |informacje o procesie||informacje o procesie 2| ...
     *
     * \param flags - parametry dla metody opisujące, które elementy zostaną uwzględnione. Takie same jak dla klasy ProcessInfo.
     * \return Łańcuch znaków opisujący wszystkie procesy.
     */
    std::string toString(unsigned flags = 0) const override;

    /*!
     * \brief Metoda pozwalająca usunąć wszelkie dostępne informacje o procesach.
     *
     * Po wywołaniu metody, aby kolejny raz otrzymać informacje o komputerze należy
     * wywołać jedną z metod update.
     */
    void clear();

  private:

    /*!
     * \brief Metoda pozwala zainicjować kontener asocjacyjny wartościami, które później zostaną wykorzystane przy metodzie update.
     *
     * Jest tworzony kontener asocjacyjny, którego kluczem jest id procesu,
     * a wartością true.
     *
     * \param [out] keysVec -kontener asocjacyjny ze wszystkimi dostępnymi procesami jako klucze i wartość true jako wartość.
     */
    void getAllProcessesIdWithStatus(std::map<unsigned,bool>& keysVec) const;

    /*!
     * \brief Kontener asocjacyjny
     *
     * Kluczem jest id procesu, wartością obiekt klasy ProcessInfo
     *
     */
    std::map<unsigned, ProcessInfo> m_processesMap;

    /*!
     * \brief Pole przechowujące ostatnio utworzone procesy
     */
    std::vector<unsigned> m_lastAddedProcesses;

    /*!
     * \brief Pole przechowujące ostatnio usunięte procesy
     */
    std::vector<unsigned> m_lastDeletedProcesses;
};

#endif /* PROCESSESVECTOR_HPP_ */
