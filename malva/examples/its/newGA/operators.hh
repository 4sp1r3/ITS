#ifndef OPERATORS__HH
#define OPERATORS__HH

#include "newGAstructures.hh"
#include "solution.hh"
#include "population.hh"

skeleton newGA
{

    requires class Intra_Operator {
    protected:
        unsigned int _number_operator;
        float *probability;

    public:
        Intra_Operator(const unsigned int _number_op);
        virtual ~Intra_Operator();

        static Intra_Operator *create(const unsigned int _number_op);
        friend ostream & operator<<(ostream& os, const Intra_Operator& intra);

        virtual void execute(Rarray<Solution*>& sols) const = 0;
        virtual void setup(char line[MAX_BUFFER]) = 0;
        unsigned int number_operator() const;

        virtual void RefreshState(const StateCenter& _sc) const = 0;
        virtual void UpdateFromState(const StateCenter& _sc) = 0;
    };

    // Crossover  ----------------------------------------------------------------------------------

    requires class Crossover : public Intra_Operator {
    public:
        Crossover();
        virtual ~Crossover();

        friend ostream & operator <<(ostream& os, const Crossover& cross);

        void cross(Solution &sol1, Solution &sol2) const;
        virtual void execute(Rarray<Solution*>& sols) const;
        virtual void setup(char line[MAX_BUFFER]);

        virtual void RefreshState(const StateCenter& _sc) const;
        virtual void UpdateFromState(const StateCenter& _sc);
    };

    // Mutation ----------------------------------------------------------------------------------

    requires class Mutation : public Intra_Operator {
    public:
        Mutation();
        virtual ~Mutation();

        friend ostream & operator<<(ostream& os, const Mutation& mutation);

        void mutate(Solution& sol) const;
        // applies mutation over all solutions in array sols
        virtual void execute(Rarray<Solution*>& sols) const;
        virtual void setup(char line[MAX_BUFFER]);

        virtual void RefreshState(const StateCenter& _sc) const;
        virtual void UpdateFromState(const StateCenter& _sc);

    };

    // Inter_Operator ( abstract )-----------------------------------------------------------

      provides class Inter_Operator
      {
    	protected:
    		unsigned int migration_rate;
    		unsigned int migration_size;
    		unsigned int migration_selection_1;
    	   	unsigned int migration_selection_2;
    	   	unsigned int migration_selection_conf_1;
    	   	unsigned int migration_selection_conf_2;

    		unsigned int _number_operator;
    	   	const Direction direction;

    	public:
    		Inter_Operator(const unsigned int _number_op, const Direction dir);
    	   	virtual ~Inter_Operator();

    	   	friend ostream& operator<< (ostream& os, const Inter_Operator& inter);

    	   	virtual void execute(Population& pop,const unsigned long current_generation,NetStream& _netstream,const bool synchronized,const unsigned int check_asyncrhonous) const=0;
    	   	virtual void setup(char line[MAX_BUFFER]);
    	   	unsigned int number_operator() const;

    	   	virtual void RefreshState(const StateCenter& _sc) const;
    	   	virtual void UpdateFromState(const StateCenter& _sc);
      };


      provides class Migration: public Inter_Operator
      {
    	public:
    		Migration(const Direction dir);
    		virtual ~Migration();

    		friend ostream& operator<< (ostream& os, const Migration& migration);

    	   	virtual void execute(Population& pop,const unsigned long current_generation,NetStream& _netstream,const bool synchronized,const unsigned int check_asyncrhonous) const;
      };

    // Selection ( Makes a random selection ) -----------------------------------------

      provides class Selection
      {
    	protected:
    		unsigned int _number_selection;
    	  	const Direction direction;

    	public:

    		Selection(const Direction dir);
     	  	Selection(const unsigned int _number_sel, const Direction dir);
    		virtual ~Selection();

    		friend ostream& operator<< (ostream& os, const Selection& sel);

           	virtual void prepare(Rarray<struct individual>& fitness_values,const bool remplace); // const;
    	  	virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int dummy,const bool remplace) const;
    	  	unsigned int number_selection() const;
      };

    // Selection_Tournament  ---------------------------------------------------------------------------------

      provides class Selection_Tournament: public Selection
      {
    	public:
    		Selection_Tournament(const Direction dir);
    		virtual ~Selection_Tournament();

    		friend ostream& operator<< (ostream& os, const Selection_Tournament& sel);

    		virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int tourment_size,const bool remplace) const;
      };

    // Selection_Roulette_Wheel  ---------------------------------------------------------------------------------

      provides class Selection_Roulette_Wheel: public Selection
      {
    	public:
    		Selection_Roulette_Wheel(const Direction);
    		virtual ~Selection_Roulette_Wheel();

    		friend ostream& operator<< (ostream& os, const Selection_Roulette_Wheel& sel);

           	virtual void prepare(Rarray<struct individual>& fitness_values,const bool remplace); // const;
    		virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int dummy,const bool remplace) const;
      };

    // Selection_Rank  ---------------------------------------------------------------------------------

      provides class Selection_Rank: public Selection
      {
    	public:
    		Selection_Rank(const Direction dir);
    		Selection_Rank(const unsigned int _number_sel, const Direction dir);
    		virtual ~Selection_Rank();

    		friend ostream& operator<< (ostream& os, const Selection_Rank& sel);

            virtual void prepare(Rarray<struct individual>& fitness_values,const bool remplace); // const;
    		virtual void reset();

    		virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int portion,const bool remplace) const;
      };

    // Selection_Best  ---------------------------------------------------------------------------------

      provides class Selection_Best: public Selection_Rank
      {
    	private:
    		mutable unsigned int selection_best_position;

    	public:
    		Selection_Best(const Direction);
    		virtual ~Selection_Best();

    		friend ostream& operator<< (ostream& os, const Selection_Best& sel);

    		virtual void reset();
           	virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int position,const bool remplace) const;
      };

    // Selection_Worst  ---------------------------------------------------------------------------------

      provides class Selection_Worst: public Selection_Rank
      {
    	private:
    		mutable unsigned int selection_worst_position;

    	public:
    		Selection_Worst(const Direction);
    		virtual ~Selection_Worst();

    		friend ostream& operator<< (ostream& os, const Selection_Worst& sel);

    		virtual void reset();
    		virtual struct individual select_one(const Rarray<Solution*>& to_select_1,const Rarray<Solution*>& to_select_2,const Rarray<struct individual>& fitness_values,const unsigned int position,const bool remplace) const;
      };

    // Operator_Pool -------------------------------------------------------------------------

     // pool with all operators and selections that can be chosen in the setup file
      provides class Operator_Pool
      {
    	private:
    		mutable Rlist<Intra_Operator>	_intra_operators;
     		Rlist<Selection>	_selectors;
     		Rlist<Inter_Operator> 	_inter_operators;

    	public:
    		Operator_Pool(const Problem& pbm);
    		~Operator_Pool();

    		Intra_Operator& intra_operator(const unsigned int index) const;
    		Rlist<Intra_Operator>& intra_operators() const;
    		Selection& selector(const unsigned int index) const;
    		const Rlist<Selection>& selectors() const;
    		Inter_Operator& inter_operator(const unsigned int index) const;
    		const Rlist<Inter_Operator>& inter_operators() const;

      };

}

#endif
