/**
 *
 * @file    PseudoBide.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#ifndef PSEUDOBIDE_H
#define PSEUDOBIDE_H

#include "AbstractClosedPseudoSequence.h"
#include "functions.h"

/**
 * @class PseudoBide
 * @brief Closed-sequential-pattern algorithm BIDE (for single item sequences)
 * @param Chord
 */
class PseudoBide : public AbstractClosedPseudoSequence
{

public :

    /********** Member functions **********/

    /**
	 * @brief Run bide
	 * @param sequence
	 * @return
	 */
	 set<list<Chord> > run(const list<list<set<Chord> > >& sequence);

	/**
	 * @brief First bide call
	 * @return
	 */
	 set<list<Chord> > bide();

	/**
	 * @brief Recursive bide call
	 * @param currentDB
	 * @param seqPrefix
	 */
	 void bide(const map<list<set<Chord> >, int>& currentDB,
               const list<Chord>& seqPrefix);

	/**
	 * @brief Whether a forward extension is possible
	 *        Are there any extensions, that have at least the support
	 *        to be an extension
	 * @param freq
	 * @param currentSupport
	 * @return
	 */
	 bool frequentExtensionItems(const map<Chord, int>& freq,
                                 int currentSupport);

	/**
	 * @brief Test whether the specified prefix can be processed any further
	 *        (means: is not included already)
	 * @param prefix
	 * @param currentDB
	 * @return
	 */
	 bool backScan(const list<Chord>& prefix,
                   const map<list<set<Chord> >, int>& currentDB);

	/**
	 * @brief Checks closedness by whether there is an backward expansion
	 *        for the given prefix.
	 *        It checks whether an element can be added before the end of
	 *        the given prefix for all db sequences. Therefore the prefix is
	 *        broken in two parts. For the first part the first minimal complete
	 *        subsequence is removed containing the part, for the second part,
	 *        the last minimal complete subsequence containing it, is removed.
	 *        If there's an element common in all these periods of the database,
	 *        one knows that the sequence can be expanded by this element.
	 *        Therefore the prefix is not a closed sequence. This check is done
	 *        for all possible expansion slots in the prefix.
	 * @param prefix
	 * @param currentDB
	 * @return
	 */
	 bool backwardClosednessCheck(const list<Chord>& prefix,
                                  const map<list<set<Chord> >, int>& currentDB);

	/**
	 * @brief Get the borders for periods of the given prefix
	 * @param prefix
	 * @param currentSequence
	 * @return
	 */
	 vector<vector<int> >
	 getPeriodBorders(const list<Chord>& prefix,
                      const list<set<Chord> >& currentSequence);

};

#endif
