#pragma once

template <typename T>
struct Type{};

template <typename Key, typename Value, typename State>
struct Authenticator
{
      using Self = Authenticator<Key, Value, State>;
      
      template <typename ConcreteState>
      Authenticator (const unordered_map<Key, Value>& map, Type<ConcreteState>) : m_map (map), m_state (new ConcreteState(*this)) {
            
      }
      
      void processKey (const Key& key)
      {
            m_state -> processKey (key);
      }
      
      void processValue (const Value& value)
      {
            m_state -> processValue (value);
      }
      
      bool authenticated () const
      {
            return m_state -> authenticated ();
      }
      
      bool keyAuthenticated () const
      {
            return m_state -> keyAuthenticated ();
      }
      
      bool valueAuthenticated () const
      {
            return m_state -> valueAuthenticated ();
      }
      
      friend ostream& operator<< (ostream& os, const Self& self)
      {
            os << *self.m_state;
            return os;
      }
      
private:
      const unordered_map<Key, Value>& m_map;
      State* m_state;
      
      friend State;
};

template <typename Key, typename Value>
struct AuthenticationState
{
      using Self = AuthenticationState<Key, Value>;
      using Auth = Authenticator<Key, Value, Self>;
      
      AuthenticationState (Auth& authenticator) : m_authenticator(authenticator), m_map (authenticator.m_map), m_authenticated (false)
      {
            
      }
      
      virtual ~AuthenticationState ()
      {
            
      }
      
      virtual void processKey (const Key& key) // email
      {
            
      }
      
      virtual void processValue (const Value& value) // email
      {
            
      }
      
      bool authenticated () const
      {
            return m_authenticated;
      }
      
      virtual bool keyAuthenticated () const = 0;
      
      virtual bool valueAuthenticated () const = 0;
      
      virtual void print (ostream& os) const
      {
            os << "AuthenticationState";
      }
      
      friend ostream& operator<< (ostream& os, const Self& self)
      {
            self.print (os);
            return os;
      }
      
      operator const Auth& ()
      {
            return m_authenticator;
      }
      
private:
      Authenticator<Key, Value, Self>& m_authenticator;
      bool m_authenticated;
      
protected:
      const unordered_map<Key, Value>& m_map;
      
      
      template <typename NewConcreteState>
      void changeState ()
      {
            m_authenticator.m_state = new NewConcreteState (m_authenticator);
            delete this;
      }
      
      template <typename NewConcreteState, class T>
      void changeState (const T& t)
      {
            m_authenticator.m_state = new NewConcreteState (t, m_authenticator);
            delete this;
      }
      
      template <typename NewConcreteState>
      void changeState (NewConcreteState* state)
      {
            m_authenticator.m_state = state;
            delete this;
      }
      
      template <typename NewConcreteState>
      void changeStateAndProcessKey (const Key& key)
      {
            m_authenticator.m_state = new NewConcreteState (m_authenticator);
            m_authenticator.processKey(key);
            delete this;
      }
      
      template <typename NewConcreteState>
      void changeStateAndProcessValue (const Value& value)
      {
            m_authenticator.m_state = new NewConcreteState (m_authenticator);
            m_authenticator.processValue(value);
            delete this;
      }
      
      optional<Value> find (const Key& key)
      {
            typename unordered_map<Key, Value>::const_iterator i = m_map.find(key);
            
            if ( i != m_map.end() ) {
                  return (*i).second;
            }
            return {};
      }
      
};

template <typename Key, typename Value = typename Key::Value>
struct KeyNotAuthenticated;
template <typename Key, typename Value = typename Key::Value>
struct KeyAuthenticated;
template <typename Key, typename Value = typename Key::Value>
struct Authenticated;


template <typename Key, typename Value>
struct KeyNotAuthenticated : AuthenticationState<Key, Value>
{
      using Base = AuthenticationState<Key, Value>;
      using Auth = typename Base::Auth;
      
      KeyNotAuthenticated (Auth& authenticator) : Base (authenticator)
      {
            
      }
      
      virtual ~KeyNotAuthenticated ()
      {
            
      }
      
      void processKey (const Key& key) // email
      {
            auto value = Base::find (key);
            if ( value.has_value() ) {
                  //                  const Value& v = value.value();
                  Base::template changeState<KeyAuthenticated<Key, Value>>(value.value());
            }
            
      }
      
      virtual bool keyAuthenticated () const
      {
            return false;
      }
      
      virtual bool valueAuthenticated () const
      {
            return false;
      }
      
      virtual void print (ostream& os) const
      {
            os << "KeyNotAuthenticated";
      }
};



template <typename Key, typename Value>
struct KeyAuthenticated : AuthenticationState<Key, Value>
{
      using Base = AuthenticationState<Key, Value>;
      using AuthenticationState<Key, Value>::AuthenticationState;
      
      template <typename Auth>
      KeyAuthenticated (const Value& value, Auth& auth) : m_value (value), Base (auth)
      {
            
      }
      
      virtual ~KeyAuthenticated ()
      {
            
      }
      
      void processKey (const Key& key) // email
      {
            Base::template changeStateAndProcessKey<KeyNotAuthenticated<Key, Value>>(key);
      }
      
      void processValue (const Value& value)
      {
            if ( m_value == value ) {
                  Base::template changeState<Authenticated<Key, Value>>(m_value);
            }
      }
      
      virtual bool keyAuthenticated () const
      {
            return true;
      }
      
      virtual bool valueAuthenticated () const
      {
            return false;
      }
      
      virtual void print (ostream& os) const
      {
            os << "KeyAuthenticated";
      }
      
private:
      Value m_value;
};

template <typename Key, typename Value>
struct Authenticated : AuthenticationState<Key, Value>
{
      using Base = AuthenticationState<Key, Value>;
      
      template <typename Auth>
      Authenticated (const Value& value, Auth& auth) : AuthenticationState<Key, Value> (auth), m_value (value)
      {
            
      }
      
      void processKey (const Key& key) // email
      {
            Base::template changeStateAndProcessKey<KeyNotAuthenticated<Key, Value>>(key);
      }
      
      void processValue (const Value& value)
      {
            Base::template changeState<KeyAuthenticated<Key, Value>>(m_value);
      }
      
      virtual bool keyAuthenticated () const
      {
            return true;
      }
      
      virtual bool valueAuthenticated () const
      {
            return true;
      }
      
      virtual void print (ostream& os) const
      {
            os << "Authenticated";
      }
      
private:
      Value m_value;
};
