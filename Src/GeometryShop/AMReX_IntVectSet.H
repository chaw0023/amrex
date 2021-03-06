#ifndef AMREX_IntVectSet_H_
#define AMREX_IntVectSet_H_

#include "AMReX_Box.H"
#include <unordered_set>

using namespace std;
namespace amrex
{
  class IVSIterator;

  struct lex_compare_iv
  {
    bool operator() (const IntVect& lhs, const IntVect& rhs) const
    {
      //w.c. changed IntVect::operator< to do the right thing
      return lhs < rhs;
    }
  };

  /// IntVectSet implementation based std::unordered_set
  /**
   */
  class IntVectSet
  {
  public:
    friend class IVSIterator; 

    ///
    IntVectSet(){;}

    ///
    IntVectSet(const Box& a_box);

    ///
    IntVectSet(const IntVectSet& a_sivs);

    ///
    ~IntVectSet(){;}

    ///
    IntVectSet (IntVectSet&& a_rhs) = default;

    ///
    IntVectSet& operator= (IntVectSet&& a_rhs) = default;

    ///
    void define(const Box&);

    ///
    void define(const IntVectSet& a_sivs);

    ///
    IntVectSet& operator=(const IntVectSet& a_sivs);

    ///or
    IntVectSet& operator|=(const IntVectSet& a_sivs);

    ///
    IntVectSet& operator|=(const IntVect& a_iv);

    ///
    IntVectSet& operator|=(const Box& a_box);

    ///and
    IntVectSet& operator&=(const IntVectSet& s_sivs);

    ///and
    IntVectSet& operator&=(const Box& a_box);


    ///not
    IntVectSet& operator-=(const IntVectSet& a_sivs);

    ///not
    IntVectSet& operator-=(const IntVect& a_iv);

    ///not
    IntVectSet& operator-=(const Box& a_box);

    ///returns true if
    bool operator==(const IntVectSet& lhs) const;

    ///
    bool contains(const IntVect& iv) const;

    ///
    bool contains(const Box& box) const;

    ///
    bool contains(const IntVectSet& ivs) const;

    ///
    void grow(int igrow);

    ///
    void grow(int idir, int igrow);

    ///
    void growHi();

    ///
    void growHi(int a_dir);

    ///
    void refine(int iref = 2);

    ///
    void coarsen(int iref = 2);

    ///
    void shift(const IntVect& iv);

    ///
    void clear();

    ///
    Box minBox() const;

    ///
    bool isEmpty() const;

    ///
    void makeEmpty() ;

    ///
    int numPts() const;


    void define(const Vector<IntVect>& a_vect);

    ///
    size_t linearSize() const;

    ///
    void linearOut(void* buffer ) const;

    ///
    void linearIn(const void* const buffer );

    using container_type = std::unordered_set<IntVect, IntVect::shift_hasher>;
    container_type::iterator begin () { return m_stdSet.begin(); }
    container_type::const_iterator begin() const { return m_stdSet.begin(); }
    container_type::const_iterator cbegin() const { return m_stdSet.cbegin(); }
    container_type::iterator end () { return m_stdSet.end(); }
    container_type::const_iterator end() const { return m_stdSet.end(); }
    container_type::const_iterator cend() const { return m_stdSet.cend(); }
      
  private:

    void getVectorIV(Vector<IntVect>& a_vect) const;
    container_type m_stdSet;
  };

  ///
  class IVSIterator
  {
  public:
    ///
    IVSIterator();

    ///
    IVSIterator(const IntVectSet& ivs);

    ///
    void define(const IntVectSet& ivs);

    ///
    const IntVect& operator()() const ;

    ///
    bool ok() const;

    ///
    void operator++();

    ///
    void begin();

    ///
    void end();

    ///
    void clear();
  private:
    const IntVectSet* m_ivs;
//    std::set<IntVect, lex_compare_iv>::iterator m_iter;
    IntVectSet::container_type::const_iterator m_iter;
  };

  IntVectSet intersect (const IntVectSet& a, const IntVectSet& b, const Box& bx);
  IntVectSet intersect (const IntVectSet& ivs, const Box& bx);
}
#endif //  STDSETIVS_H
