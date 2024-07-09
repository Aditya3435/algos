#define ll long long
/*
Make Changes only to 3 functions
    -combine (for how tree will behave add, max, min gcd, xor)
    -apply (apply an update)
    -combineUpdate (updates combined updates)

    // To start in main function

    case 1: only 1 updatation
        ST<ll,ll> st(n+1, 0, -1)// n+1->ST for size (n+1), identity element is zero(taking sum), identity_update = -1(mostly)
        st.build(vector);// to build
        print(st.query(l,r)) returns acculumulated (min,max,addition)
        st.update(l,r,val) // for point update l == r

        Changes to be made-
        
        -remove update structure from above

        T apply(T curr, U upd, ll tl, ll tr) // tl to tr is range, upd->update function 
        {
            T ans;
            ans = (tr-tl+1)*upd;
            return ans;
        }

        U combineUpdate(U old_upd, U new_upd, ll tl, ll tr)
        {
            U ans;
            ans = old_upd;
            ans = new_upd;
            return ans;
        }  
    case 2: more than 1 updatation
        
        -make changes in update structure

        Update upd(-1,0); // -1,0 are identity elements and whole Update is called identity updates setvalue, increment(for eg.) 
        ST<ll,Update> st(n+1, 0, upd)// n+1->ST for size (n+1), identity element is zero(taking sum), identity_update = upd(for multiple updates)
        st.build(vector);// to build
        print(st.query(l,r)) returns acculumulated (min,max,addition)

        // increment update(assuming l and r taken)
            Update upd(-1,x)
            st.update(l,r,upd) // for point update l == r
        // setval update(assuming l and r taken)
            Update upd(x,0)
            st.update(l,r,upd) // for point update l == r
*/


// struct Update {
//     // 2 updates set value to x, and increment value to x, in range(l,r)
//     ll setval;
//     ll increment;
//     // *** first set the value to setval then increase it by incremetn
//     Update() {
//         setval = -1;
//         increment = 0;
//     }
//     Update(ll setval, ll increment) {
//         this->setval = setval;
//         this->increment = increment;
//     }
//     bool operator==(const Update& other) const {
//         return setval == other.setval && other.increment; // to check correct datatype of updates
//     }
// };

/* ---------- Assigns different index for same element ...............*/

// Coordinate compression (when array size <=1e5, and elements <=1e18, and we want to use elements as indexs)
// returns indexng from 0
// vll convertArray(vll& v) {
    // vpll p;
    // ll n = v.sz;
    // fl(i,0,n) p.pb({v[i], i});
    // sort(be(p));
    // vll nv(v.size());
    // fl(i,0,n) nv[p[i].ss] = i;
    // return nv = v;
// }


/*

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int x, int y) {
        return a[x] < a[y];
    });
    for(auto i : id) {
        
    }

*/
/* ---------- Assigns same index for same element ...............*/
// returns indexing from 1

// vll normalize(vector<ll> &v){
//     vector<ll> aux = v;
//     sort(aux.begin(), aux.end());
//     aux.erase(unique(aux.begin(), aux.end()), aux.end());
//     for (int i = 0; i < v.size(); i++)
//         v[i] = lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin() + 1;
//     return v;
// }

// int aux[maxN];
// int normalize(int *arr, int size) {
//     copy(arr, arr + size, aux);
//     sort(aux, aux + size);
//     int newSize = unique(aux, aux + size) - aux;
//     for (int i = 0; i < size; i++) {
//         arr[i] = lower_bound(aux, aux + newSize, arr[i]) - aux + 1;
//     }
//     return size;
// }

const int maxN = 2e5 + 1;
int n;
ll seg[10*maxN];
template<class T, class U>
struct ST{
    T combine(T l, T r){
        return max(l,r);
    }
    ll n;
    T identity_element;
    U identity_update;

    ST(ll n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
    }
    void update(int k, int k1, ll x) { // point update
        k += n; seg[k] = x; k >>= 1;
        while (k > 0) {
            seg[k] = combine(seg[2*k], seg[2*k+1]);
            k >>= 1;
        }
    }

    ll query(int a, int b) {
        a += n, b += n;
        ll s = 0;
        while (a <= b) {
            if (a & 1) {
                s = combine(s, seg[a]);
                a++;
            }
            if (~b & 1) {
                s = combine(s, seg[b]);
                b--;
            }
            a >>= 1, b >>= 1;
        }
        return s;
    }
    pll elementIndex(ll l, ll r) {
        ll idx = 0;
        ll res = query(l,r);
        ll i = l, j = r;
        while(i<=j) {
            ll mid = i + j>>1;
            if(query(l,mid)==res) {
                idx = mid;
                j = mid - 1;
            }
            else i = mid + 1;
        } 
        return {res, idx};
    }
};



template<class T, class U>
struct ST{
    vector<T>st;
    vector<U>lazy;
    ll n;
    T identity_element;
    U identity_update;

    ST(ll n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(5*n,identity_element);
        lazy.assign(5*n, identity_update);
    }


    T combine(T l, T r)
    {
        return l+r;
    }


    void buildUtil(ll v, ll tl, ll tr, vector<T>&a)
    {
        if(tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        ll tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }


    T apply(T curr, U upd, ll tl, ll tr)  // add previous update to curr seg tree node
    {
        T ans = curr;
        // for increment ans += (tr-tl+1)*upd;
        ans = (tr-tl+1)*upd;
        return ans;
    }

    U combineUpdate(U old_upd, U new_upd, ll tl, ll tr) // add previous update to lazy tree node
    {
        U ans;
      
        ans = old_upd;
        ans = new_upd;
        return ans;
    }  


    void push_down(ll v, ll tl, ll tr)
    {
        
        //(when update is not integer) for the below line to work, make sure the "==" operator is defined for U.
        if(lazy[v] == identity_update)return;
        st[v] = apply(st[v], lazy[v], tl, tr); // add previous update to curr seg tree node
        if(2*v + 1 <= 4*n || tl != tr)
        {
            ll tm = (tl + tr)>>1;
            lazy[2*v + 1] = combineUpdate(lazy[2*v+1], lazy[v], tl, tm);
            lazy[2*v + 2] = combineUpdate(lazy[2*v+2], lazy[v], tm+1,tr);            
        }
        lazy[v] = identity_update;
    }
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r)
    {
        push_down(v,tl,tr);
        if(l > r)return identity_element;
        if(tr < l or tl > r)
        {
            return identity_element;
        }
        if(l <= tl and r >= tr)
        {
            return st[v];
        }
        ll tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
 
    void updateUtil(ll v, ll tl, ll tr, ll l, ll r, U upd)
    {
        push_down(v,tl,tr); 
        if(tr < l or tl > r)return;
        if(tl >=l and tr <=r) // [l....(tl, tr)......r]
        {
            lazy[v] = combineUpdate(lazy[v],upd,tl,tr);
            push_down(v,tl,tr);
        }
        else
        {
            ll tm = (tl + tr)>>1;
            updateUtil(2*v+1,tl,tm,l,r,upd);
            updateUtil(2*v+2,tm+1,tr,l,r,upd);
            st[v] = combine(st[2*v + 1], st[2*v+2]);
        }
    }

    void build(vector<T>a)
    {
        assert( (ll)a.size() == n);
        buildUtil(0,0,n-1,a);
    }
    T query(ll l, ll r)
    {
        return queryUtil(0,0,n-1,l,r);
    }
    void update(ll l,ll r, U upd)
    {
        updateUtil(0,0,n-1,l,r,upd);
    }
    pll elementIndex(ll l, ll r) {
        ll idx = 0;
        ll res = query(l,r);
        ll i = l, j = r;
        while(i<=j) {
            ll mid = i + j>>1;
            if(query(l,mid)==res) {
                idx = mid;
                j = mid - 1;
            }
            else i = mid + 1;
        } 
        return {res, idx};
    }
};


