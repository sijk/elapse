<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>build_system_integration</name>
    <title>Build system integration</title>
    <filename>build_system_integration</filename>
    <docanchor file="build_system_integration">other_build_systems</docanchor>
    <docanchor file="build_system_integration">qmake</docanchor>
    <docanchor file="build_system_integration">cmake</docanchor>
  </compound>
  <compound kind="page">
    <name>coding_conventions</name>
    <title>Coding conventions</title>
    <filename>coding_conventions</filename>
    <docanchor file="coding_conventions">headers</docanchor>
    <docanchor file="coding_conventions">smart_pointers</docanchor>
  </compound>
  <compound kind="page">
    <name>qtvideosink_overview</name>
    <title>qtvideosink / qtglvideosink / qwidgetvideosink</title>
    <filename>qtvideosink_overview</filename>
    <docanchor file="qtvideosink_overview">overview</docanchor>
    <docanchor file="qtvideosink_overview">usage_with_qtgstreamer</docanchor>
    <docanchor file="qtvideosink_overview">usage_without_qtgstreamer</docanchor>
    <docanchor file="qtvideosink_overview">qt5_support</docanchor>
  </compound>
  <compound kind="page">
    <name>internal_design_details</name>
    <title>Internal Design Details</title>
    <filename>internal_design_details</filename>
    <docanchor file="internal_design_details">connect_design</docanchor>
    <docanchor file="internal_design_details">value_design</docanchor>
    <docanchor file="internal_design_details">wrap_design</docanchor>
  </compound>
  <compound kind="namespace">
    <name>QGlib</name>
    <filename>namespaceQGlib.html</filename>
    <class kind="class">QGlib::Error</class>
    <class kind="class">QGlib::ObjectBase</class>
    <class kind="class">QGlib::Object</class>
    <class kind="class">QGlib::Interface</class>
    <class kind="class">QGlib::ParamSpec</class>
    <class kind="class">QGlib::Signal</class>
    <class kind="class">QGlib::Quark</class>
    <class kind="class">QGlib::RefPointer</class>
    <class kind="class">QGlib::RefCountedObject</class>
    <class kind="class">QGlib::Type</class>
    <class kind="struct">QGlib::ValueVTable</class>
    <class kind="class">QGlib::Value</class>
    <class kind="struct">QGlib::ValueImpl</class>
    <member kind="typedef">
      <type>RefPointer&lt; ParamSpec &gt;</type>
      <name>ParamSpecPtr</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a33e7ae9b7088e97465da55dfd5d84a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>RefPointer&lt; Object &gt;</type>
      <name>ObjectPtr</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a01fbfc9bb914b63b11b4610d6aa9b1eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ConnectFlag</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af5cc53bb011d8c44d8669da601d57979</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ConnectAfter</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af5cc53bb011d8c44d8669da601d57979ad625c7e44b2dd771209174d0ba37c2db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PassSender</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af5cc53bb011d8c44d8669da601d57979a1c01e8e1eafeb6f7ba80875219bb43d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>connect</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ac98fa9d9848416fb5737b4c097113c7d</anchor>
      <arglist>(void *instance, const char *detailedSignal, T *receiver, R(T::*slot)(Args...), ConnectFlags flags=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>disconnect</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a3fc346a069eb0fb9a1c693bb5dcfa318</anchor>
      <arglist>(void *instance, const char *detailedSignal=0, T *receiver=0, R(T::*slot)(Args...)=0)</arglist>
    </member>
    <member kind="function">
      <type>R</type>
      <name>emit</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aa6af5d11b620e54164301ca1eb233580</anchor>
      <arglist>(void *instance, const char *detailedSignal, const Args &amp;...args)</arglist>
    </member>
    <member kind="function">
      <type>R</type>
      <name>emitWithDetail</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>acb8f9efa1b1627df9bb6944c4b1b1a3b</anchor>
      <arglist>(void *instance, const char *signal, Quark detail, const Args &amp;...args)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a1446bde33057db455b2ce6d5f83a4412</anchor>
      <arglist>(QDebug dbg, const Error &amp;error)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a5310bcfa257ea7ad50f1605468100bbc</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::RunFirst)==static_cast&lt; int &gt;(G_SIGNAL_RUN_FIRST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ad37be7c3f6e6fb2243b7aa4ff1515e63</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::RunLast)==static_cast&lt; int &gt;(G_SIGNAL_RUN_LAST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ad94bb4d7e2de31d436da25dd52c5531a</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::RunCleanup)==static_cast&lt; int &gt;(G_SIGNAL_RUN_CLEANUP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a540a859cf86cf6bcf67bcd954bbca99e</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::NoRecurse)==static_cast&lt; int &gt;(G_SIGNAL_NO_RECURSE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a2127680e4a61510410570db902a8938b</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::Detailed)==static_cast&lt; int &gt;(G_SIGNAL_DETAILED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a41f6eceb7a667f77b2d7a9e06b570f14</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::Action)==static_cast&lt; int &gt;(G_SIGNAL_ACTION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aba55032ae03e34f6eb3795e7b23da5a9</anchor>
      <arglist>(static_cast&lt; int &gt;(Signal::NoHooks)==static_cast&lt; int &gt;(G_SIGNAL_NO_HOOKS))</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>ParamSpec_new</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a19b6879268bf79387e1d83e966922416</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a3ab6daf3d21bf3397ed9579fd314cd3c</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::Readable)==static_cast&lt; int &gt;(G_PARAM_READABLE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a9636c76c1bf2d3856be34abe1403a30c</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::Writable)==static_cast&lt; int &gt;(G_PARAM_WRITABLE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ab7f40c2bb80da7497948d1e727905d2e</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::ReadWrite)==static_cast&lt; int &gt;(G_PARAM_READWRITE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a820f12ab7ac5bcbcc617cdd916d3e77a</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::Construct)==static_cast&lt; int &gt;(G_PARAM_CONSTRUCT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a7c59d3c383f3334b175a707cfb2f8cb0</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::ConstructOnly)==static_cast&lt; int &gt;(G_PARAM_CONSTRUCT_ONLY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af5c102ae088d26f22388c8ee11c8aafe</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::LaxValidation)==static_cast&lt; int &gt;(G_PARAM_LAX_VALIDATION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a9a0ce6ee5e05f38abc573b23cf728ec1</anchor>
      <arglist>(static_cast&lt; int &gt;(ParamSpec::Deprecated)==static_cast&lt; int &gt;(G_PARAM_DEPRECATED))</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Object_new</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ada2a985271c08da32cf8915203950d05</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Interface_new</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a00a40c78023ed9829e11104dccfc10a7</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ab7bc62d590c7430bc3588397653d7e37</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Invalid)==static_cast&lt; int &gt;(G_TYPE_INVALID))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aa71fd372e2b2edab9e8fb5ae7352cfe5</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::None)==static_cast&lt; int &gt;(G_TYPE_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a638cab5a62f63d3e0fcdb0cc79aebf03</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Interface)==static_cast&lt; int &gt;(G_TYPE_INTERFACE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a8b390e3137dd793a4b53bc2ba424bb36</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Char)==static_cast&lt; int &gt;(G_TYPE_CHAR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a4409feb3426a6d5906384f8e6afdea16</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Uchar)==static_cast&lt; int &gt;(G_TYPE_UCHAR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a4c07933e6421cd6e30193b3a2c056ff6</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Boolean)==static_cast&lt; int &gt;(G_TYPE_BOOLEAN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af7f23929bc8ddabd451acc631ba15728</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Int)==static_cast&lt; int &gt;(G_TYPE_INT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>acdf1015e196825b7364775a24dd5b070</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Uint)==static_cast&lt; int &gt;(G_TYPE_UINT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aa574cff0bb685c14159f88f83877e799</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Long)==static_cast&lt; int &gt;(G_TYPE_LONG))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af429023b632808419d7019b6330bef42</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Ulong)==static_cast&lt; int &gt;(G_TYPE_ULONG))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aaf854725910abf0e1918d68f739b4955</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Int64)==static_cast&lt; int &gt;(G_TYPE_INT64))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a8044b888f078b5b24dd129d111b69136</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Uint64)==static_cast&lt; int &gt;(G_TYPE_UINT64))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a326eebc07765d5a243333831921cea3d</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Enum)==static_cast&lt; int &gt;(G_TYPE_ENUM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a701964e8817dd973d27c26fb291c24cd</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Flags)==static_cast&lt; int &gt;(G_TYPE_FLAGS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a0f1bfefed82d6365605d9f6c7e7e850d</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Float)==static_cast&lt; int &gt;(G_TYPE_FLOAT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a0e331becf96294fc8a9f4246c16de7a8</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Double)==static_cast&lt; int &gt;(G_TYPE_DOUBLE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a88685be1b00ba510b29ab797808e00c5</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::String)==static_cast&lt; int &gt;(G_TYPE_STRING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ae576ddc20f92233c81fcb12f1b30e0cf</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Pointer)==static_cast&lt; int &gt;(G_TYPE_POINTER))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>aa1c210c782bb84b785410d384f13855a</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Boxed)==static_cast&lt; int &gt;(G_TYPE_BOXED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>af854530416cfefea2275a83d3c920a59</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Param)==static_cast&lt; int &gt;(G_TYPE_PARAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a6aa189371ed9e20aff1d958dcff352ea</anchor>
      <arglist>(static_cast&lt; int &gt;(Type::Object)==static_cast&lt; int &gt;(G_TYPE_OBJECT))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ab0b2b3812b6b3cb3d013ff19a27992ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>GetType</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>ad8819833f5c4f201fa0f70e9aa5583ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a0cb8c9c49f309a24c1d47c0acfac5469</anchor>
      <arglist>(QDebug debug, const Value &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>RefCountedObject *</type>
      <name>constructWrapper</name>
      <anchorfile>namespaceQGlib.html</anchorfile>
      <anchor>a38d6938270323a67d389f1fb67150fe0</anchor>
      <arglist>(Type instanceType, void *instance)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Error</name>
    <filename>classQGlib_1_1Error.html</filename>
    <member kind="function">
      <type></type>
      <name>Error</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a0b40a3d8b8c7613dc0c1a6ee8f47afb6</anchor>
      <arglist>(GError *error=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Error</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a24222b460dc785c33332431b2f5a7ec7</anchor>
      <arglist>(Quark domain, int code, const QString &amp;message)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Error</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>af5c095507b0e3750446ea5a50f6496a0</anchor>
      <arglist>(const Error &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Error &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a4f174873639e008bf4de0b2ed92f937a</anchor>
      <arglist>(const Error &amp;other)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>what</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a4f8ee7fc7397f2c09b895bece4dfdbf9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Quark</type>
      <name>domain</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a4b51ca112901b2e75faea29481e48f1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>code</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>ac9de20b02808bbf92e4f90cb6ea74c4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>message</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>ad865bf498d226bffd4526627d1b27b09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator GError *</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a4a1fe65644e60ffff4280fd1b1775b26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const GError *</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a2f4ba6981759948a67841958c1d154e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Error</type>
      <name>copy</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a94406063bcabf631814b418de523d5a4</anchor>
      <arglist>(GError *error)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classQGlib_1_1Error.html</anchorfile>
      <anchor>a97bad78951fbbaa2251bb8f45ee694a9</anchor>
      <arglist>(QDebug dbg, const Error &amp;error)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::ObjectBase</name>
    <filename>classQGlib_1_1ObjectBase.html</filename>
    <base>QGlib::RefCountedObject</base>
    <member kind="function">
      <type>ParamSpecPtr</type>
      <name>findProperty</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a77fe9ee2271178aa0189a80ef1388d64</anchor>
      <arglist>(const char *name) const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; ParamSpecPtr &gt;</type>
      <name>listProperties</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a5afbeca00a97d82ad4d348bb53c68c8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Value</type>
      <name>property</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a852119e7de7846f269eec3802a6d85e3</anchor>
      <arglist>(const char *name) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setProperty</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>adf757a291146e056785c7cd7e720bb6d</anchor>
      <arglist>(const char *name, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setProperty</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>aa2c298b4f7a93345bd68f7101323c01d</anchor>
      <arglist>(const char *name, const Value &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>data</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>ac5bb87c34a7174e86ab020aea385154b</anchor>
      <arglist>(const char *key) const </arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>stealData</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a227e6a039c8c28e4f53a7b2dd82b541e</anchor>
      <arglist>(const char *key) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setData</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a25890a5962123ed6a9fd90b095869d19</anchor>
      <arglist>(const char *key, void *data, void(*destroyCallback)(void *)=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>quarkData</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>a6add6b31e330e51ee76074cb530023f2</anchor>
      <arglist>(const Quark &amp;quark) const </arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>stealQuarkData</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>ae176e3a6bd29bb10ca265018b8674f6c</anchor>
      <arglist>(const Quark &amp;quark) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setQuarkData</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>acdd167eb78f1262abd3aff07952d38bf</anchor>
      <arglist>(const Quark &amp;quark, void *data, void(*destroyCallback)(void *)=NULL)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>ae8ce666aca3950f4823e3b01aa427fc3</anchor>
      <arglist>(bool increaseRef)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGlib_1_1ObjectBase.html</anchorfile>
      <anchor>ab178cb04ebc9cdbcaca8c3f5ecc84cfa</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Object</name>
    <filename>classQGlib_1_1Object.html</filename>
    <base virtualness="virtual">QGlib::ObjectBase</base>
  </compound>
  <compound kind="class">
    <name>QGlib::Interface</name>
    <filename>classQGlib_1_1Interface.html</filename>
    <base virtualness="virtual">QGlib::ObjectBase</base>
  </compound>
  <compound kind="class">
    <name>QGlib::ParamSpec</name>
    <filename>classQGlib_1_1ParamSpec.html</filename>
    <base>QGlib::RefCountedObject</base>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>abc74b4efb2767f0ff912482177e3707c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>nick</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a0a7946e6a634c138f44033e3c8e727cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>description</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a79c065bb1cb2772ec9beb40543b52abb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ParamFlags</type>
      <name>flags</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>affb503ef2a6eb58bb7399f06375a39b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>valueType</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a0a2be5d2217da3a1771e52f88a1763dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>ownerType</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a6f87b0db696dda68a9e3650a28564cfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>quarkData</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>ac47338790dedd7375dcfb2f901f4664e</anchor>
      <arglist>(const Quark &amp;quark) const </arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>stealQuarkData</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a6ec22edb4b2d56348ca724d3d226df96</anchor>
      <arglist>(const Quark &amp;quark) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setQuarkData</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a42b0d90dfa438d218531e52cf738c5ce</anchor>
      <arglist>(const Quark &amp;quark, void *data, void(*destroyCallback)(void *)=NULL)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a807d8c32befc7d6e4f38b76e4f3794c6</anchor>
      <arglist>(bool increaseRef)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGlib_1_1ParamSpec.html</anchorfile>
      <anchor>a43487ae5605c46b8dba074b6aeb33d3b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Signal</name>
    <filename>classQGlib_1_1Signal.html</filename>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a279c119ad6aafed428465d1969695d17</anchor>
      <arglist>(const Signal &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a86617f48555ba5783a0b4f559a28021a</anchor>
      <arglist>(const Signal &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>ab069cbc374c3f7c41e2d8d73dab15f2b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>id</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a71448be41f117c939c3c309442fb9b46</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a38aec45ec5e9b56f81f1ab81cf9d8068</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SignalFlags</type>
      <name>flags</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>ae2438ca515ebacba6419293317180b78</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>instanceType</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a2b432270266355f260ef4a5921eb7ee7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>returnType</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>ac4161f8a5858b84ada71f01acbc8e5b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; Type &gt;</type>
      <name>paramTypes</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>a91d7e1c6893170a695f2cc4e8707af57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Signal</type>
      <name>lookup</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>af4eeb6416a7b659342069828a5a2c559</anchor>
      <arglist>(const char *name, Type type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QList&lt; Signal &gt;</type>
      <name>listSignals</name>
      <anchorfile>classQGlib_1_1Signal.html</anchorfile>
      <anchor>af2c8250cff4796d0b38f80c67502fb79</anchor>
      <arglist>(Type type)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Quark</name>
    <filename>classQGlib_1_1Quark.html</filename>
    <member kind="function">
      <type></type>
      <name>Quark</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>aa2a3bf1c21cfc8ae02c4f8d290be8dcb</anchor>
      <arglist>(quint32 gquark=0)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>toString</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>a485648bb1f15af7a4ef5f913bc6e9242</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator quint32</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>ae60872fd740e6c0be364246995c6d249</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Quark</type>
      <name>fromString</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>a398ae460993a31541cfc7e7daddcb72e</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Quark</type>
      <name>fromString</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>a0371c5c2ded70c5e48917e6051f5a2df</anchor>
      <arglist>(const QString &amp;str)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Quark</type>
      <name>tryString</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>aa54c9077d9e2b2dfce450c90bd775160</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Quark</type>
      <name>tryString</name>
      <anchorfile>classQGlib_1_1Quark.html</anchorfile>
      <anchor>aa69a8b64b6b42a9cf35870608ab30aee</anchor>
      <arglist>(const QString &amp;str)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::RefPointer</name>
    <filename>classQGlib_1_1RefPointer.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>RefPointer</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a27fba6a09048f7e2f2050f53b0ad281e</anchor>
      <arglist>(T *cppClass)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RefPointer</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a03690ff0f79d6ef53d0ae7e06d38b7ab</anchor>
      <arglist>(const RefPointer&lt; X &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RefPointer</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>ac32bb1c414f39da97cf2ca2d6d2dd35a</anchor>
      <arglist>(const RefPointer&lt; T &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>RefPointer&lt; T &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a657c51e3101ae186e4473452c2ad7dbf</anchor>
      <arglist>(const RefPointer&lt; X &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>RefPointer&lt; T &gt; &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a891e33c54c71ff3d9aca25ba05765598</anchor>
      <arglist>(const RefPointer&lt; T &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a1b911ebce7862791ebc8be76fc4d7c88</anchor>
      <arglist>(const X &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>af998ae6b654d926fcc5cfcc696c160d4</anchor>
      <arglist>(const X &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>aeeddcd144d88e07c3cfe244a6035874b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isNull</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a6796790f7cb1f6df3e9ef807be04e16c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>ab41cfcb8d427022ee14da0a12cb4fbd6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>operator-&gt;</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a17e65b79ebdea62bf19b5a327a7eebf0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator typename T::CType *</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a35cdf67d31d2975d55307cc70c485e7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RefPointer&lt; X &gt;</type>
      <name>staticCast</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>ac73840fe4a20f03392897a8c5ada54c4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>RefPointer&lt; X &gt;</type>
      <name>dynamicCast</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a296910931095de0e0c5f4a67be559f45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RefPointer&lt; T &gt;</type>
      <name>wrap</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a686e44f803afc1551ad0ab04ac620d39</anchor>
      <arglist>(typename T::CType *nativePtr, bool increaseRef=true)</arglist>
    </member>
    <member kind="function">
      <type>boost::enable_if_c&lt; boost::is_pointer&lt; X &gt;::value &amp;&amp;!boost::is_same&lt; X, typename boost::add_pointer&lt; typename T::CType &gt;::type &gt;::value, bool &gt;::type</type>
      <name>operator==</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a79f100d245605cc4f98498d9b2d88df2</anchor>
      <arglist>(const X &amp;other, const RefPointer&lt; T &gt; &amp;self)</arglist>
    </member>
    <member kind="function">
      <type>boost::enable_if_c&lt; boost::is_pointer&lt; X &gt;::value &amp;&amp;!boost::is_same&lt; X, typename boost::add_pointer&lt; typename T::CType &gt;::type &gt;::value, bool &gt;::type</type>
      <name>operator!=</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>a72b189a1199bff338536ebc60dbcf421</anchor>
      <arglist>(const X &amp;other, const RefPointer&lt; T &gt; &amp;self)</arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>qHash</name>
      <anchorfile>classQGlib_1_1RefPointer.html</anchorfile>
      <anchor>afff1e796c707b76445889f1006b7624d</anchor>
      <arglist>(const RefPointer&lt; T &gt; &amp;ptr)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::RefCountedObject</name>
    <filename>classQGlib_1_1RefCountedObject.html</filename>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGlib_1_1RefCountedObject.html</anchorfile>
      <anchor>ab24e1c5a863610af95ef22ba1ed75ef6</anchor>
      <arglist>(bool increaseRef)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGlib_1_1RefCountedObject.html</anchorfile>
      <anchor>aa0adf869d82b09478ac0cd1dc0baaa64</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>T *</type>
      <name>object</name>
      <anchorfile>classQGlib_1_1RefCountedObject.html</anchorfile>
      <anchor>a757941f25c3d990e50e56c46dd5569e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void *</type>
      <name>m_object</name>
      <anchorfile>classQGlib_1_1RefCountedObject.html</anchorfile>
      <anchor>a588d704775c4a5626300588dd505a3f8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Type</name>
    <filename>classQGlib_1_1Type.html</filename>
    <member kind="function">
      <type></type>
      <name>Type</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a63edeb0efbb5e8f8dabf233a95e6526d</anchor>
      <arglist>(Private::GType gtype)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Type</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a9e8193a4456f7719306c8e4bdb3ed0a7</anchor>
      <arglist>(FundamentalType ftype)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Type</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a824e20dec2961b3d71a496108ee9fb21</anchor>
      <arglist>(const Type &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Type &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>aac4e7c745f1a8b1e24c82417f5ed0c3b</anchor>
      <arglist>(Type other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>acfeb4ece8a7c96b84dbf47317e37f02d</anchor>
      <arglist>(Type other) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator Private::GType</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a66915f4d16cafb00d1f2c243671720f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ad521669d29f602cb32e36ecef9f7db93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Quark</type>
      <name>nameQuark</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a000e04e48f150e2e2dc8b0bdf89bb5f9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a74f77a8ef9dcecbeb2459319507650a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAbstract</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a0ebfc22aa35e6aa28f825c2f9610f121</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isDerived</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a7e455771bdd95bd41d9510bd76b38bd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFundamental</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a5484b22726f011151b890aa6e20fe8db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValueType</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ab84b6e271a4fecb374600f75be682a0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasValueTable</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a284af60e21a03c9a0f62ec89d9a74ac9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isClassed</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ac3730f9818c9196913d25bf1812434d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInstantiatable</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ae4340d528e68e786994dd7f38a54f28d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isDerivable</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a3848d45c655db722bbfe95444f6dc924</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isDeepDerivable</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a33c20a713922dba0b859fd18bb1ee4a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInterface</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ab8cf2b64f6095153a72bfd38bb0ac08f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>fundamental</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a80b439ccb188c0086ddd287f76dd0079</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>parent</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ae1127abed4e9f7817858d14390446328</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>depth</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a62039103f330b108d67a44ae0843b2ec</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>nextBase</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a03be7f40d2f307c6cf25d604320daf7f</anchor>
      <arglist>(Type rootType) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isA</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>ac3866d12df2fdd409665d06440d92072</anchor>
      <arglist>(Type is_a_type) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isA</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a4cd562dbee8096a21bbe057a80d74080</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; Type &gt;</type>
      <name>children</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>aa19c38b96b4821ce19ad477e0415baf5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; Type &gt;</type>
      <name>interfaces</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a686c5e16470a891b10676ac7c92482e1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; Type &gt;</type>
      <name>interfacePrerequisites</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>afeb08d44e718e551dbbb04beaffd9046</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>quarkData</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a2b6e3c33242f6bc955966815407f5dc1</anchor>
      <arglist>(const Quark &amp;qname) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setQuarkData</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a87010294efa99f7f600fb5d4d4f599e1</anchor>
      <arglist>(const Quark &amp;qname, void *data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Type</type>
      <name>fromInstance</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a6d7d99317c5c9fc475b0b6e28954d562</anchor>
      <arglist>(void *nativeInstance)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Type</type>
      <name>fromName</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a3c4bedc5e619254782f1ec4995feeffe</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>GetType</name>
      <anchorfile>classQGlib_1_1Type.html</anchorfile>
      <anchor>a470e0e4c1518da8a57426ee7f0ae1c1c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>QGlib::ValueVTable</name>
    <filename>structQGlib_1_1ValueVTable.html</filename>
    <member kind="typedef">
      <type>void(*</type>
      <name>SetFunction</name>
      <anchorfile>structQGlib_1_1ValueVTable.html</anchorfile>
      <anchor>aff35fb6a63c2d9a998e2d84f5ea9d4db</anchor>
      <arglist>)(Value &amp;value, const void *data)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>GetFunction</name>
      <anchorfile>structQGlib_1_1ValueVTable.html</anchorfile>
      <anchor>a57b2aafac02b2925d904c79feb649cda</anchor>
      <arglist>)(const Value &amp;value, void *data)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ValueVTable</name>
      <anchorfile>structQGlib_1_1ValueVTable.html</anchorfile>
      <anchor>ad1706ade7bfc7dd639d06f0390e60558</anchor>
      <arglist>(SetFunction s, GetFunction g)</arglist>
    </member>
    <member kind="variable">
      <type>SetFunction</type>
      <name>set</name>
      <anchorfile>structQGlib_1_1ValueVTable.html</anchorfile>
      <anchor>a8d1211d895965896b27886586b36f0e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GetFunction</type>
      <name>get</name>
      <anchorfile>structQGlib_1_1ValueVTable.html</anchorfile>
      <anchor>a3e62762183c006c8131e40ef607ffcfe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGlib::Value</name>
    <filename>classQGlib_1_1Value.html</filename>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a31fa48d8a8f36d1afe8cc32052fbe825</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a10bc0139047ea881cf79da11e2ce7f9b</anchor>
      <arglist>(const GValue *gvalue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ae104edf29043a4aef8b92b7d3776afea</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a8b85c14c37d562feacdc57b163235aa4</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a04d5e02a6298540118dddec59f7cf53a</anchor>
      <arglist>(char val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>aee9d26a3f4aa733626bd5506c27a47a9</anchor>
      <arglist>(uchar val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a27decd99622b2085b5808d417811fb36</anchor>
      <arglist>(int val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a364a77d320dc747acdcdc9223f3c2c67</anchor>
      <arglist>(uint val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a362e3b01ec8ac8f7b1e5747142e320ea</anchor>
      <arglist>(long val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ace8f68f047f1798a5709097735015c72</anchor>
      <arglist>(ulong val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a1f9634157c654af9e935091d6706329d</anchor>
      <arglist>(qint64 val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ac20aea58d6043e327ee3b0dd250b3ac6</anchor>
      <arglist>(quint64 val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a30b9fa5da56633d1c8eec4ad6911ae07</anchor>
      <arglist>(float val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a824333f899804c30ff966a2da0c4295d</anchor>
      <arglist>(double val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a9bf6997a129d385fcfedec578cf96e4a</anchor>
      <arglist>(const char *val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ab7f515fca3b3a6a9d3e72e45bf7bae3a</anchor>
      <arglist>(const QByteArray &amp;val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a3ccc31bf2dd9f00bcb800e8b694a85d2</anchor>
      <arglist>(const QString &amp;val)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Value</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a208ef339ab6336a6826528639c940b80</anchor>
      <arglist>(const Value &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Value &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a672270000e5292a29bf96b2d874f237a</anchor>
      <arglist>(const Value &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ad7cd3c078d8acc459409e475e0290d32</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a8e739f421b48ecf3885a8c7a0b53f08e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a83834eb49ae040b0ab05f3ff72afda24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>type</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a83dc8726d057c8cc37aad07a0eab96eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canTransformTo</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>abb8ffd57de5a98755568a26d7a8ce7e7</anchor>
      <arglist>(Type type) const </arglist>
    </member>
    <member kind="function">
      <type>Value</type>
      <name>transformTo</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a5f4659bdc8be12e1d49092e491312310</anchor>
      <arglist>(Type type) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a86a12ca4e717fc287a3ea986d16c4903</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>get</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ac040403fe779f737b66eb80ff639bd80</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a87014421e046084761729ba8e4c4f207</anchor>
      <arglist>(const T &amp;data)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>toBool</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a35543060abac5ea6606323918646c172</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>toChar</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a20cf6d9470b00ed457900c0ec7976462</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>uchar</type>
      <name>toUChar</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>abaff26c2c993376b647489099dad8f28</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>toInt</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>af56d85d185695a065875607850303c5b</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>toUInt</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>aea44c8f3e22d384f6cfae2f1d1b110d4</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>toLong</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ad5b9257084a4b84408161b86cd0b0eb2</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>ulong</type>
      <name>toULong</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>aa6c9fd8749ff5690f714c31f838d32c4</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>toInt64</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a98bb5faac1bbeabf3b0f9e83c4f40e35</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>toUInt64</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a5fc9a3524d5c2ab48309d0c17ab37230</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>QByteArray</type>
      <name>toByteArray</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>aab703d526c6344ab085c02d46215ab86</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>toString</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>ad0bc56c7f1326f98c8bc82b213a45bff</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>Error</type>
      <name>toError</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a4084e7eaaecace6c8cb3b8135a814f82</anchor>
      <arglist>(bool *ok=NULL) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator GValue *</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a46daf589b31c78fd6d66daebfcfa1bbe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const GValue *</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a0779706b60c9c475e053a4e01318ac3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Value</type>
      <name>create</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a1667dd06be8e40b6f9c30a1fcf572abd</anchor>
      <arglist>(const T &amp;data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>registerValueVTable</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>a8314613952d00362b94bcd71e628ba29</anchor>
      <arglist>(Type type, const ValueVTable &amp;vtable)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classQGlib_1_1Value.html</anchorfile>
      <anchor>aeb6dc3f6d41a352ba24b211ebb8eb433</anchor>
      <arglist>(QDebug debug, const Value &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>QGlib::ValueImpl</name>
    <filename>structQGlib_1_1ValueImpl.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>get</name>
      <anchorfile>structQGlib_1_1ValueImpl.html</anchorfile>
      <anchor>a504da02afa59283593b5fb0278e81e52</anchor>
      <arglist>(const Value &amp;value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>set</name>
      <anchorfile>structQGlib_1_1ValueImpl.html</anchorfile>
      <anchor>a35489805c2ebd46aaba05d0a0471f70d</anchor>
      <arglist>(Value &amp;value, const T &amp;data)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>QGst</name>
    <filename>namespaceQGst.html</filename>
    <namespace>QGst::Ui</namespace>
    <namespace>QGst::Utils</namespace>
    <namespace>QGst::Parse</namespace>
    <class kind="class">QGst::Bin</class>
    <class kind="class">QGst::Buffer</class>
    <class kind="class">QGst::BufferList</class>
    <class kind="class">QGst::BufferListIterator</class>
    <class kind="class">QGst::Bus</class>
    <class kind="class">QGst::Caps</class>
    <class kind="interface">QGst::ChildProxy</class>
    <class kind="class">QGst::Clock</class>
    <class kind="class">QGst::ClockTime</class>
    <class kind="class">QGst::ColorBalanceChannel</class>
    <class kind="class">QGst::ColorBalance</class>
    <class kind="class">QGst::Element</class>
    <class kind="class">QGst::ElementFactory</class>
    <class kind="class">QGst::Event</class>
    <class kind="class">QGst::FlushStartEvent</class>
    <class kind="class">QGst::FlushStopEvent</class>
    <class kind="class">QGst::EosEvent</class>
    <class kind="class">QGst::NewSegmentEvent</class>
    <class kind="class">QGst::TagEvent</class>
    <class kind="class">QGst::BufferSizeEvent</class>
    <class kind="class">QGst::SinkMessageEvent</class>
    <class kind="class">QGst::QosEvent</class>
    <class kind="class">QGst::SeekEvent</class>
    <class kind="class">QGst::NavigationEvent</class>
    <class kind="class">QGst::LatencyEvent</class>
    <class kind="class">QGst::StepEvent</class>
    <class kind="class">QGst::GhostPad</class>
    <class kind="class">QGst::Message</class>
    <class kind="class">QGst::EosMessage</class>
    <class kind="class">QGst::ErrorMessage</class>
    <class kind="class">QGst::WarningMessage</class>
    <class kind="class">QGst::InfoMessage</class>
    <class kind="class">QGst::TagMessage</class>
    <class kind="class">QGst::BufferingMessage</class>
    <class kind="class">QGst::StateChangedMessage</class>
    <class kind="class">QGst::StepDoneMessage</class>
    <class kind="class">QGst::StreamStatusMessage</class>
    <class kind="class">QGst::ApplicationMessage</class>
    <class kind="class">QGst::ElementMessage</class>
    <class kind="class">QGst::SegmentDoneMessage</class>
    <class kind="class">QGst::DurationMessage</class>
    <class kind="class">QGst::LatencyMessage</class>
    <class kind="class">QGst::AsyncDoneMessage</class>
    <class kind="class">QGst::RequestStateMessage</class>
    <class kind="class">QGst::StepStartMessage</class>
    <class kind="class">QGst::QosMessage</class>
    <class kind="class">QGst::MiniObject</class>
    <class kind="class">QGst::Object</class>
    <class kind="class">QGst::Pad</class>
    <class kind="class">QGst::Pipeline</class>
    <class kind="class">QGst::PluginFeature</class>
    <class kind="interface">QGst::PropertyProbe</class>
    <class kind="class">QGst::Query</class>
    <class kind="class">QGst::PositionQuery</class>
    <class kind="class">QGst::DurationQuery</class>
    <class kind="class">QGst::LatencyQuery</class>
    <class kind="class">QGst::SeekingQuery</class>
    <class kind="class">QGst::SegmentQuery</class>
    <class kind="class">QGst::ConvertQuery</class>
    <class kind="class">QGst::FormatsQuery</class>
    <class kind="class">QGst::BufferingQuery</class>
    <class kind="class">QGst::UriQuery</class>
    <class kind="class">QGst::StreamVolume</class>
    <class kind="struct">QGst::Fourcc</class>
    <class kind="struct">QGst::Fraction</class>
    <class kind="class">QGst::Structure</class>
    <class kind="class">QGst::SharedStructure</class>
    <class kind="class">QGst::TagList</class>
    <class kind="interface">QGst::UriHandler</class>
    <class kind="interface">QGst::VideoOrientation</class>
    <class kind="interface">QGst::XOverlay</class>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Bin &gt;</type>
      <name>BinPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac2e7463ade9c76c41d57108456146fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Bus &gt;</type>
      <name>BusPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a66a55aab785600e8d2cab237db763953</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Caps &gt;</type>
      <name>CapsPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a72dfcb0d3a1bebbf5e718d22ab55cce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ChildProxy &gt;</type>
      <name>ChildProxyPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a72e2604c24aaf2b909c1f21d821019f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Clock &gt;</type>
      <name>ClockPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aea6f58641a08e654fb80337512f7b368</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ColorBalanceChannel &gt;</type>
      <name>ColorBalanceChannelPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a25497a7156dc404a75ccd5cd419a12d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ColorBalance &gt;</type>
      <name>ColorBalancePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad42e8b02337922bac95d43289cce7357</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Discoverer &gt;</type>
      <name>DiscovererPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af4117305ad484d0c26b334c37b3b9c19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererInfo &gt;</type>
      <name>DiscovererInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a53438d2d5e56cced57d49ec370065d0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererStreamInfo &gt;</type>
      <name>DiscovererStreamInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a49c5f54738d32f88d9b9ad00d2a04149</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererContainerInfo &gt;</type>
      <name>DiscovererContainerInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af81353a252061c9bbe36a73c0d71d6b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererAudioInfo &gt;</type>
      <name>DiscovererAudioInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a770b7329f93319b0b8940c01b7c0c1af</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererVideoInfo &gt;</type>
      <name>DiscovererVideoInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a77ea20ea1ee764674e76fd93eac4cf9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DiscovererSubtitleInfo &gt;</type>
      <name>DiscovererSubtitleInfoPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6f34f1898e9af8746226a88fad3f435f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Element &gt;</type>
      <name>ElementPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a626100a4ca10b394c1e708faf7af2748</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ElementFactory &gt;</type>
      <name>ElementFactoryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6b933926aa3398e940a6f71535617931</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; GhostPad &gt;</type>
      <name>GhostPadPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a202cc093d1ee503894a5d5bddbcd78be</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Message &gt;</type>
      <name>MessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aab724d050647454e96a5ba4b82af2b06</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; EosMessage &gt;</type>
      <name>EosMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abb17a5b39823b494f97fce5a0b3ebb68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ErrorMessage &gt;</type>
      <name>ErrorMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aab55c770414ec455e1446c49bab2d72a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; WarningMessage &gt;</type>
      <name>WarningMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7c23258d18dd66d72aee34467b8bb84f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; InfoMessage &gt;</type>
      <name>InfoMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a05794a9db1d809b96e3aa8fba3f7dfdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; TagMessage &gt;</type>
      <name>TagMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0e825a72e1d548a71645985d343abdba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; BufferingMessage &gt;</type>
      <name>BufferingMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ade9e3207e04551b35e17a23f80405aee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StateChangedMessage &gt;</type>
      <name>StateChangedMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a70fd0669ad6de2f413abaf8beb6126b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StepDoneMessage &gt;</type>
      <name>StepDoneMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa5a56a1a2bb1889ab34c8a32b105af20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StreamStatusMessage &gt;</type>
      <name>StreamStatusMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ada9a4edad29d83a6886d3c5bbd7d1003</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ApplicationMessage &gt;</type>
      <name>ApplicationMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9046761f0acc43a1ac03b533123ebcf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ElementMessage &gt;</type>
      <name>ElementMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4c39aa55c9ee541052080d88081f78ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; SegmentDoneMessage &gt;</type>
      <name>SegmentDoneMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a26ecd4a5d51ed746b947cdd76d36f72e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DurationMessage &gt;</type>
      <name>DurationMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4bb08292109c8c756301e99c8b069a2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; LatencyMessage &gt;</type>
      <name>LatencyMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a88ca921a4e188b924a6a61094318ccaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; AsyncDoneMessage &gt;</type>
      <name>AsyncDoneMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a03283af7b7cf38a5dc828452c166dfd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; RequestStateMessage &gt;</type>
      <name>RequestStateMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa98b1350c5f2fff071c117126aaf414f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StepStartMessage &gt;</type>
      <name>StepStartMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5550ae283b9574fe8a618d9edb58c938</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; QosMessage &gt;</type>
      <name>QosMessagePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac2642f25e0b89c1a67b097ade4250ccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; MiniObject &gt;</type>
      <name>MiniObjectPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a49a6719d889cc49f965ad66555e8adfe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Object &gt;</type>
      <name>ObjectPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a91aa053a492fc1f497ade61f653627a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Pad &gt;</type>
      <name>PadPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a501ae94bf2d27d3f25d8896b90e5bc23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Pipeline &gt;</type>
      <name>PipelinePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a49b039fdca163e52000a7e5c2c31c489</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; PluginFeature &gt;</type>
      <name>PluginFeaturePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5e787f511adeb461f0f3daa9d1e82890</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; PropertyProbe &gt;</type>
      <name>PropertyProbePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad3234946a50eb4d9e0efe29d9d8c678c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Query &gt;</type>
      <name>QueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aea1028f0a34d0ab023d057ff64a4aac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; PositionQuery &gt;</type>
      <name>PositionQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aabc5105971c53a001f0d11f0d08f8351</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; DurationQuery &gt;</type>
      <name>DurationQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6c45802a45d07cc6d162d4dd85a6ec21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; LatencyQuery &gt;</type>
      <name>LatencyQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abda641b02a2c9eb93e76fe060f803636</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; SeekingQuery &gt;</type>
      <name>SeekingQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a454094c22af15ce87016668db1877ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; SegmentQuery &gt;</type>
      <name>SegmentQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af3cc91a4eab5451a04a068f99bed0a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; ConvertQuery &gt;</type>
      <name>ConvertQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9965796ed670f5124b3581f88d633ee0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; FormatsQuery &gt;</type>
      <name>FormatsQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af537ee26fb4b2cc44161d1b87ce21c4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; BufferingQuery &gt;</type>
      <name>BufferingQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>acc251b49410bad6d567a592a3e7b4d08</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; UriQuery &gt;</type>
      <name>UriQueryPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>afca9df8cd7dc3e3fc8feba3ae373084d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Buffer &gt;</type>
      <name>BufferPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a688869f5774a81b434c3cb7c2d4ad60a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; BufferList &gt;</type>
      <name>BufferListPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a45e400c4d6c0bee26c4fa5559fc671d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; Event &gt;</type>
      <name>EventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3a31e96c89c0e706eb42cc5b949ff2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; FlushStartEvent &gt;</type>
      <name>FlushStartEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a562036d027e8efd8955d1f6694b9dc70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; FlushStopEvent &gt;</type>
      <name>FlushStopEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9f9d6c4ec4508b1485c351226968445d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; EosEvent &gt;</type>
      <name>EosEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aff30dcf7d80adfeaffb4d5a36656eb1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; NewSegmentEvent &gt;</type>
      <name>NewSegmentEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae9253f9e76f1f4da46bb4122fdf70820</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; TagEvent &gt;</type>
      <name>TagEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7e408bacaa0252abc04c39b687e4c3e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; BufferSizeEvent &gt;</type>
      <name>BufferSizeEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8a4c2c64efe8d13274198a8389fa16b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; SinkMessageEvent &gt;</type>
      <name>SinkMessageEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7c4404a2d6744a48265f3843c8d71ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; QosEvent &gt;</type>
      <name>QosEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab97081416b70d44721612f798b4050fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; SeekEvent &gt;</type>
      <name>SeekEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4018a8e1912bcbfc2c7ea4d29792d982</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; NavigationEvent &gt;</type>
      <name>NavigationEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6529376e243a97bd21f9fc80e5398b4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; LatencyEvent &gt;</type>
      <name>LatencyEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7b7c854c2461f22c4fa180d33f8188d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StepEvent &gt;</type>
      <name>StepEventPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a240f5fa757f994d629500c343d3e0ec2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; StreamVolume &gt;</type>
      <name>StreamVolumePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a84c142cd672057d516f49672565e86b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QSharedPointer&lt; SharedStructure &gt;</type>
      <name>StructurePtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4c6e40aed407325d2a9d5c809cf5810e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; UriHandler &gt;</type>
      <name>UriHandlerPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a58cec9f46d42e5f980fe57a66e69e069</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; VideoOrientation &gt;</type>
      <name>VideoOrientationPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa224be4d3d25505e8be8c3f2b3d00e8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>QGlib::RefPointer&lt; XOverlay &gt;</type>
      <name>XOverlayPtr</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a434d8dc76612e1129e3e7a43a307e174</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Private::Range&lt; int &gt;</type>
      <name>IntRange</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae5c0c360516048e66d9159bfe16f7d85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Private::Range&lt; qint64 &gt;</type>
      <name>Int64Range</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab6dcada6ba448d135da7b84656daaf00</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Private::Range&lt; double &gt;</type>
      <name>DoubleRange</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6c0db12a431625a11c91608809fb31df</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Private::Range&lt; Fraction &gt;</type>
      <name>FractionRange</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aac9e5cffdd67da946bcecf57ad0c5752</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4157726f59efa9867a4c44ae5512ae9b</anchor>
      <arglist>(QDebug debug, const CapsPtr &amp;caps)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a94f7b3c1a0918c494ae20e3590b0d63a</anchor>
      <arglist>(QDebug debug, DiscovererResult result)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName&lt; DiscovererStreamInfoPtr &gt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6d27143ad212aba9cbfd7a2436d1d443</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName&lt; DiscovererContainerInfoPtr &gt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac77bff0c810dcc14aea3155fadd3055f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName&lt; DiscovererAudioInfoPtr &gt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aeb571d4e767b54af3d5a0d0e8184fea6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName&lt; DiscovererVideoInfoPtr &gt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abaf352d1b89f05c32c895ec61992268c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>typeName&lt; DiscovererSubtitleInfoPtr &gt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a48b7c4f40ed3c5302bf888c259ba4578</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>printStreamInfoDetails</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a36cca60049bb5376143622c82d9eae44</anchor>
      <arglist>(QDebug debug, const DiscovererStreamInfoPtr &amp;)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>ChildProxy_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4f79dfef49eb0cdaf5d2581c533de8b5</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>GhostPad_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab4e5d580fb512293ee62f02b591b0f22</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Pad_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a74ff43447c8cc9e1c629039d614e396b</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>UriHandler_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0486fdf181949b4b4e35c63854a6b8f2</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>MiniObject_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5922a6f7f6345ab3a6773cae71c39554</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Element_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a66fdd2805ba8e1789ab32eacf4a88727</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererStreamInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a731f9919ddfad7c9d75584501a9dd040</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererContainerInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>adcc8e767d804c0639489d60c1895ebe0</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererAudioInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9107cd946302f749557d8e92657960c6</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererVideoInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5d175ff739ddc1c45c505712f53722d1</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererSubtitleInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2c31784ca4d1a66b9e3c23800fe685ba</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>DiscovererInfo_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af714202c1f3a3f81aabcbb1f51e810c6</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Discoverer_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a17f5f377add21e7639ca2195c8265d77</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Bin_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1e64bc255a9045d602ad819d67a1bb57</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Message_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0597abb3ca33ff23b861f36a7e9ac64d</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Buffer_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a908848ebc6a139d571d4b24f8a61aab2</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Object_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af470f963009c389669f6d0eec5d7ae5c</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>StreamVolume_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3e06523b1e739f12e36355ee9930dcec</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>PluginFeature_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9912311fddf442a0b1b386f9114c8154</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Pipeline_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a17665f36ddd33d9f8e719f5441c1f524</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Clock_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2b04409efd92930d87ada67a9553350b</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>ElementFactory_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a058dcde2c08d6b441cf3304c66bcbbf5</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>ColorBalanceChannel_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad77f7e527146acc7cfa4fcdcc66310d1</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>ColorBalance_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab44574ce0235ddc64afb913baa0905e9</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>XOverlay_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab7fbce50f16b2431bbe47f1e19890a64</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Event_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ada46eeb84804ff4a5b040fdc5842b6a9</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>BufferList_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8b3625df145ebe817cfd3098792255b1</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Bus_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6ab95fb3306a3e5977d0ae72a5dee18c</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a20d4d37d8abad4cc0d847e5322dd92e5</anchor>
      <arglist>(static_cast&lt; int &gt;(MiniObjectFlagReadonly)==static_cast&lt; int &gt;(GST_MINI_OBJECT_FLAG_READONLY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa67b3e5c0d110204929e4a60eaa8e292</anchor>
      <arglist>(static_cast&lt; int &gt;(MiniObjectFlagLast)==static_cast&lt; int &gt;(GST_MINI_OBJECT_FLAG_LAST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4c2463fecf651bf52dbe5fe47bdc55f4</anchor>
      <arglist>(static_cast&lt; int &gt;(ObjectDisposing)==static_cast&lt; int &gt;(GST_OBJECT_DISPOSING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2b27a9ed643866495e67644f6f78c607</anchor>
      <arglist>(static_cast&lt; int &gt;(ObjectFloating)==static_cast&lt; int &gt;(GST_OBJECT_FLOATING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1512dc1454e7e8adc1a28c2e45bb3620</anchor>
      <arglist>(static_cast&lt; int &gt;(ObjectFlagLast)==static_cast&lt; int &gt;(GST_OBJECT_FLAG_LAST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6c94a309dd247739d8cc07ec8db606a5</anchor>
      <arglist>(static_cast&lt; int &gt;(StateVoidPending)==static_cast&lt; int &gt;(GST_STATE_VOID_PENDING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac03997e2dec701ae98333485d1f737c5</anchor>
      <arglist>(static_cast&lt; int &gt;(StateNull)==static_cast&lt; int &gt;(GST_STATE_NULL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0234c2d5c5f59a41f4f21f5f0ed5a299</anchor>
      <arglist>(static_cast&lt; int &gt;(StateReady)==static_cast&lt; int &gt;(GST_STATE_READY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6dfbaa56a38075ab6ac7b981327d4f45</anchor>
      <arglist>(static_cast&lt; int &gt;(StatePaused)==static_cast&lt; int &gt;(GST_STATE_PAUSED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a39fbc34d4ebfe74ca9a811f1be483dac</anchor>
      <arglist>(static_cast&lt; int &gt;(StatePlaying)==static_cast&lt; int &gt;(GST_STATE_PLAYING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6ec10a0ac33b3d354c48b55a0f12afa1</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeNullToReady)==static_cast&lt; int &gt;(GST_STATE_CHANGE_NULL_TO_READY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a935b383f10b2e3907e7baa1ccbda5b6e</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeReadyToPaused)==static_cast&lt; int &gt;(GST_STATE_CHANGE_READY_TO_PAUSED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8ff4435b33745fc1359f66c50a5d6231</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangePausedToPlaying)==static_cast&lt; int &gt;(GST_STATE_CHANGE_PAUSED_TO_PLAYING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a536209c6b95f9b69b624d8d4f71dd2bf</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangePlayingToPaused)==static_cast&lt; int &gt;(GST_STATE_CHANGE_PLAYING_TO_PAUSED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a85391423c944a91c0e5f321aa9edaecc</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangePausedToReady)==static_cast&lt; int &gt;(GST_STATE_CHANGE_PAUSED_TO_READY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a648018ddc78bad3dbd14389d6e166437</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeReadyToNull)==static_cast&lt; int &gt;(GST_STATE_CHANGE_READY_TO_NULL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a38d9bf24ac934044a24c61e1f50b41ef</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeFailure)==static_cast&lt; int &gt;(GST_STATE_CHANGE_FAILURE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a366270e02e14a5db9805fd7fd6ebf953</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeSuccess)==static_cast&lt; int &gt;(GST_STATE_CHANGE_SUCCESS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a13b1d15b0bcb3b09a6a64989b5e587cd</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeAsync)==static_cast&lt; int &gt;(GST_STATE_CHANGE_ASYNC))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a40e8ee24a44360d61f8dc591df6f27b7</anchor>
      <arglist>(static_cast&lt; int &gt;(StateChangeNoPreroll)==static_cast&lt; int &gt;(GST_STATE_CHANGE_NO_PREROLL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6658c976fca8c7252be80841a25a66e2</anchor>
      <arglist>(static_cast&lt; int &gt;(PadUnknown)==static_cast&lt; int &gt;(GST_PAD_UNKNOWN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>afb76f4f92f80c0872c1ceee7c6aa1c6a</anchor>
      <arglist>(static_cast&lt; int &gt;(PadSrc)==static_cast&lt; int &gt;(GST_PAD_SRC))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a15ea6c0bb0dc195caa949626dfdbde1b</anchor>
      <arglist>(static_cast&lt; int &gt;(PadSink)==static_cast&lt; int &gt;(GST_PAD_SINK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad767cdeb25210d5d79d71535445d53f7</anchor>
      <arglist>(static_cast&lt; int &gt;(PadBlocked)==static_cast&lt; int &gt;(GST_PAD_BLOCKED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6c7dcab7e9d19d3d2d93e8a80329a056</anchor>
      <arglist>(static_cast&lt; int &gt;(PadFlushing)==static_cast&lt; int &gt;(GST_PAD_FLUSHING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab2269e857952a37abc8eb0c91feb8c5e</anchor>
      <arglist>(static_cast&lt; int &gt;(PadInGetCaps)==static_cast&lt; int &gt;(GST_PAD_IN_GETCAPS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a12e99174e294677d47965ad1bce40e01</anchor>
      <arglist>(static_cast&lt; int &gt;(PadInSetCaps)==static_cast&lt; int &gt;(GST_PAD_IN_SETCAPS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>acb332e7abe4e565dd54b7068eb56a037</anchor>
      <arglist>(static_cast&lt; int &gt;(PadBlocking)==static_cast&lt; int &gt;(GST_PAD_BLOCKING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abedff5c5f291b0d5e8bf1ce19f7ab83b</anchor>
      <arglist>(static_cast&lt; int &gt;(PadFlagLast)==static_cast&lt; int &gt;(GST_PAD_FLAG_LAST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a35f2e5d5ac15d145155d9c229ba9072a</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkOk)==static_cast&lt; int &gt;(GST_PAD_LINK_OK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a379712ee48d4b5e80d7a67b7567fad84</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkWrongHierarchy)==static_cast&lt; int &gt;(GST_PAD_LINK_WRONG_HIERARCHY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1b9db67180c3af162ae8c552f5de4555</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkWasLinked)==static_cast&lt; int &gt;(GST_PAD_LINK_WAS_LINKED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5c3387db382376827612b692f2d5fa5f</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkWrongDirection)==static_cast&lt; int &gt;(GST_PAD_LINK_WRONG_DIRECTION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6f6ba9615f33a29adbcbc7170ae5dc51</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkNoFormat)==static_cast&lt; int &gt;(GST_PAD_LINK_NOFORMAT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aaaedb4058ed2fc2ea21b248c5ee419b0</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkNoSched)==static_cast&lt; int &gt;(GST_PAD_LINK_NOSCHED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad7f501f9c3c96b536c10897f2222ce7b</anchor>
      <arglist>(static_cast&lt; int &gt;(PadLinkRefused)==static_cast&lt; int &gt;(GST_PAD_LINK_REFUSED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abf4cdf002a2b6723bbfa20307d854fe0</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowCustomSuccess)==static_cast&lt; int &gt;(GST_FLOW_CUSTOM_SUCCESS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6c92c432ef80a3f4f84547892afda1a2</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowResend)==static_cast&lt; int &gt;(GST_FLOW_RESEND))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9d4246ed60bf14107fdd61d065854f3a</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowOk)==static_cast&lt; int &gt;(GST_FLOW_OK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a45468a61531bc9f8722ccf2dfda05ba8</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowNotLinked)==static_cast&lt; int &gt;(GST_FLOW_NOT_LINKED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6474c2916eed86a74a88c43ff5f8fa91</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowWrongState)==static_cast&lt; int &gt;(GST_FLOW_WRONG_STATE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6ee091a9fdc5bf95f9ce8f37aa40467f</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowUnexpected)==static_cast&lt; int &gt;(GST_FLOW_UNEXPECTED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af5f8a862ff6e569b5fec8a3995893243</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowNotNegotiated)==static_cast&lt; int &gt;(GST_FLOW_NOT_NEGOTIATED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4679f05ce5397a22dc70f4e5a8d9525a</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowError)==static_cast&lt; int &gt;(GST_FLOW_ERROR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af021fec8c08cfa485721e702bc976eea</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowNotSupported)==static_cast&lt; int &gt;(GST_FLOW_NOT_SUPPORTED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a67375e97e3f6a7490e0ee9fb1fa866d4</anchor>
      <arglist>(static_cast&lt; int &gt;(FlowCustomError)==static_cast&lt; int &gt;(GST_FLOW_CUSTOM_ERROR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7e11b2c2681a7935d84006cdafdb4099</anchor>
      <arglist>(static_cast&lt; int &gt;(ActivateNone)==static_cast&lt; int &gt;(GST_ACTIVATE_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a31443904d92979af58c639241b8db17c</anchor>
      <arglist>(static_cast&lt; int &gt;(ActivatePush)==static_cast&lt; int &gt;(GST_ACTIVATE_PUSH))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a17b86fd5a273e35aca73ee0f319d5eda</anchor>
      <arglist>(static_cast&lt; int &gt;(ActivatePull)==static_cast&lt; int &gt;(GST_ACTIVATE_PULL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab862eca3a41417600959441778d1aca0</anchor>
      <arglist>(static_cast&lt; int &gt;(RankNone)==static_cast&lt; int &gt;(GST_RANK_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>adbccd69aaeab9109e7c74ca9b53cc62c</anchor>
      <arglist>(static_cast&lt; int &gt;(RankMarginal)==static_cast&lt; int &gt;(GST_RANK_MARGINAL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a498b0d62f9549a458fdd98af23d5a02d</anchor>
      <arglist>(static_cast&lt; int &gt;(RankSecondary)==static_cast&lt; int &gt;(GST_RANK_SECONDARY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9b38f37af8e28d58844e9a2ea35d82cd</anchor>
      <arglist>(static_cast&lt; int &gt;(RankPrimary)==static_cast&lt; int &gt;(GST_RANK_PRIMARY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a758b4976845273a7addc2211095118fe</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageUnknown)==static_cast&lt; int &gt;(GST_MESSAGE_UNKNOWN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a696cadf2d3d96e74361b2ad64451da3b</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageEos)==static_cast&lt; int &gt;(GST_MESSAGE_EOS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4b41df72fa7513570d57d5b4745cf081</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageError)==static_cast&lt; int &gt;(GST_MESSAGE_ERROR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a868aa5b44920aa017305be65a66400aa</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageWarning)==static_cast&lt; int &gt;(GST_MESSAGE_WARNING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae652ed4d3b1950cd0db8fc6533c202ed</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageInfo)==static_cast&lt; int &gt;(GST_MESSAGE_INFO))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8c5ea78d286fac8ab0f3a53e9257d905</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageTag)==static_cast&lt; int &gt;(GST_MESSAGE_TAG))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae037a606e7f4ca09ce7859bd1e6acab4</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageBuffering)==static_cast&lt; int &gt;(GST_MESSAGE_BUFFERING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af4e4bf35de4f28afc003d67c3fdc8b5d</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStateChanged)==static_cast&lt; int &gt;(GST_MESSAGE_STATE_CHANGED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aeee88b7da76d688ee3b082f1951118e5</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStateDirty)==static_cast&lt; int &gt;(GST_MESSAGE_STATE_DIRTY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af0800e9d0a83293f0877cc8369d28667</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStepDone)==static_cast&lt; int &gt;(GST_MESSAGE_STEP_DONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a99480baf2d0708219191fa52bc5b9366</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageClockProvide)==static_cast&lt; int &gt;(GST_MESSAGE_CLOCK_PROVIDE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3a0f8adda7f4edd9c90fb5b1d1101554</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageClockLost)==static_cast&lt; int &gt;(GST_MESSAGE_CLOCK_LOST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a18aac315e14dd42f4f691aeb35ee592d</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageNewClock)==static_cast&lt; int &gt;(GST_MESSAGE_NEW_CLOCK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8d24894152d8ffcd7fc39d1741a46a05</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStructureChange)==static_cast&lt; int &gt;(GST_MESSAGE_STRUCTURE_CHANGE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a78f32a9017555a99e7c0eb0617215bb7</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStreamStatus)==static_cast&lt; int &gt;(GST_MESSAGE_STREAM_STATUS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af5dab592ef603fabe8d2d6377331c293</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageApplication)==static_cast&lt; int &gt;(GST_MESSAGE_APPLICATION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad2b26b2924e998f1f967a7809af0466a</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageElement)==static_cast&lt; int &gt;(GST_MESSAGE_ELEMENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a709d15401ff738da74198671d9e7add0</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageSegmentStart)==static_cast&lt; int &gt;(GST_MESSAGE_SEGMENT_START))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa06d7cf7fd4a60be0b9d7b7eaa01bc0a</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageSegmentDone)==static_cast&lt; int &gt;(GST_MESSAGE_SEGMENT_DONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae70649ac2654ae733a87f1cefa63e844</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageDuration)==static_cast&lt; int &gt;(GST_MESSAGE_DURATION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a629235075c7fa9350c788ce7e79db0fd</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageLatency)==static_cast&lt; int &gt;(GST_MESSAGE_LATENCY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad94253d966b91735c3b89dfecce18496</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageAsyncStart)==static_cast&lt; int &gt;(GST_MESSAGE_ASYNC_START))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a852aac36461c9ce7fd770c7c5b5f2bbe</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageAsyncDone)==static_cast&lt; int &gt;(GST_MESSAGE_ASYNC_DONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0766af9631605d1c4b54a28864f11c4e</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageRequestState)==static_cast&lt; int &gt;(GST_MESSAGE_REQUEST_STATE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9163551c3509d626fe8d8c99d37304a5</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageStepStart)==static_cast&lt; int &gt;(GST_MESSAGE_STEP_START))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a24d9af10489d16914cd5e8fe6fe697e2</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageQos)==static_cast&lt; int &gt;(GST_MESSAGE_QOS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>adfce361cc380b7f61600c4aa234a8660</anchor>
      <arglist>(static_cast&lt; int &gt;(MessageAny)==static_cast&lt; int &gt;(GST_MESSAGE_ANY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2fb9264e59a7503df17016c624599d61</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorSyntax)==static_cast&lt; int &gt;(GST_PARSE_ERROR_SYNTAX))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>abc51e6371d17f24a6928f4a785315ff5</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorNoSuchElement)==static_cast&lt; int &gt;(GST_PARSE_ERROR_NO_SUCH_ELEMENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8eb92740c8fce0ca4e1c07b9e3d8e983</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorNoSuchProperty)==static_cast&lt; int &gt;(GST_PARSE_ERROR_NO_SUCH_PROPERTY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aac7d898272858c598288f562441eba6e</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorLink)==static_cast&lt; int &gt;(GST_PARSE_ERROR_LINK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1af964f29a9ca95c90e6b35f9b9d94df</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorCouldNotSetProperty)==static_cast&lt; int &gt;(GST_PARSE_ERROR_COULD_NOT_SET_PROPERTY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a76068c8fd0ff0ea12d39b04380958d08</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorEmptyBin)==static_cast&lt; int &gt;(GST_PARSE_ERROR_EMPTY_BIN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab72a7bc885dd20b40ca3ee754de537d7</anchor>
      <arglist>(static_cast&lt; int &gt;(ParseErrorEmpty)==static_cast&lt; int &gt;(GST_PARSE_ERROR_EMPTY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a19a286439d5999d06c0cfa5358e70a75</anchor>
      <arglist>(static_cast&lt; int &gt;(UriUnknown)==static_cast&lt; int &gt;(GST_URI_UNKNOWN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a991a92cf1679a20d0060ea3bfcdf75b6</anchor>
      <arglist>(static_cast&lt; int &gt;(UriSink)==static_cast&lt; int &gt;(GST_URI_SINK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a52b9739e7a56c53f55911f0ab5449485</anchor>
      <arglist>(static_cast&lt; int &gt;(UriSrc)==static_cast&lt; int &gt;(GST_URI_SRC))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7da95879b9c608033c69e843df90db87</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferingStream)==static_cast&lt; int &gt;(GST_BUFFERING_STREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af300eb6386964889b1147825383d00a1</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferingDownload)==static_cast&lt; int &gt;(GST_BUFFERING_DOWNLOAD))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8c19b73b50a9dcec54b8c7e8294b1245</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferingTimeshift)==static_cast&lt; int &gt;(GST_BUFFERING_TIMESHIFT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0ee5644af39863ad6f21812a281e2fd4</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferingLive)==static_cast&lt; int &gt;(GST_BUFFERING_LIVE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af41e5315627b8f8c2b31bf8ce0224ec4</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatUndefined)==static_cast&lt; int &gt;(GST_FORMAT_UNDEFINED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a44ad570d8b0546303f0c65f7487142b9</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatDefault)==static_cast&lt; int &gt;(GST_FORMAT_DEFAULT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2181e088225e5d6b6540898fb047f89d</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatBytes)==static_cast&lt; int &gt;(GST_FORMAT_BYTES))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac32c8f47e931df179d8025b5a0d465b8</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatTime)==static_cast&lt; int &gt;(GST_FORMAT_TIME))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a68ca85acf0f8f2ce8e62839958977c41</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatBuffers)==static_cast&lt; int &gt;(GST_FORMAT_BUFFERS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a74d24b0b7784eb5a3607a31abed45771</anchor>
      <arglist>(static_cast&lt; int &gt;(FormatPercent)==static_cast&lt; int &gt;(GST_FORMAT_PERCENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7842525437d84569ed9bbd0aa8de3c24</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeCreate)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_CREATE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad5ceabe3a1ef9f31c917ebd3d57fe203</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeEnter)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_ENTER))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad8e8261a910af175bfb13b736900d95c</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeLeave)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_LEAVE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8758de3965feb344a4c77292472ebcf8</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeDestroy)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_DESTROY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1556975d42753a96853f9da90496a22a</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeStart)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_START))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8938fb1be625aaf7f10a25100d5f61aa</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypePause)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_PAUSE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a63782c33cafa35076f38bb83889f60e4</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamStatusTypeStop)==static_cast&lt; int &gt;(GST_STREAM_STATUS_TYPE_STOP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5dcbd97d60e18d24ee57f9e92362cd7e</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamVolumeFormatLinear)==static_cast&lt; int &gt;(GST_STREAM_VOLUME_FORMAT_LINEAR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a843661b81ede1c485fd16104d72fd180</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamVolumeFormatCubic)==static_cast&lt; int &gt;(GST_STREAM_VOLUME_FORMAT_CUBIC))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a88b8c1789747e213193b74cc729e211b</anchor>
      <arglist>(static_cast&lt; int &gt;(StreamVolumeFormatDb)==static_cast&lt; int &gt;(GST_STREAM_VOLUME_FORMAT_DB))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0ec61dbf04aa5a388ed25664c42f363f</anchor>
      <arglist>(static_cast&lt; int &gt;(ColorBalanceHardware)==static_cast&lt; int &gt;(GST_COLOR_BALANCE_HARDWARE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3c1a572ccce03142f0c47e41f1544aad</anchor>
      <arglist>(static_cast&lt; int &gt;(ColorBalanceSoftware)==static_cast&lt; int &gt;(GST_COLOR_BALANCE_SOFTWARE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a35797630304ab9b1daf8e0fdc1bd7b23</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryNone)==static_cast&lt; int &gt;(GST_QUERY_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a21016fb22ae4eeacb40b5ffc6e12c055</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryPosition)==static_cast&lt; int &gt;(GST_QUERY_POSITION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a90202968b7d513ad5a92b3fbdc5d856f</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryDuration)==static_cast&lt; int &gt;(GST_QUERY_DURATION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a76655f627e4b94b9912bd53bc75e1ef3</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryLatency)==static_cast&lt; int &gt;(GST_QUERY_LATENCY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad24e47351e20d15e2273d235a7e4f19b</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryJitter)==static_cast&lt; int &gt;(GST_QUERY_JITTER))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a58fe9b888de6fa533f213051a179e523</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryRate)==static_cast&lt; int &gt;(GST_QUERY_RATE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a97a41333c72b4481e871777342da8f09</anchor>
      <arglist>(static_cast&lt; int &gt;(QuerySeeking)==static_cast&lt; int &gt;(GST_QUERY_SEEKING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a98b6f78e8bdf240548bfbda25044b890</anchor>
      <arglist>(static_cast&lt; int &gt;(QuerySegment)==static_cast&lt; int &gt;(GST_QUERY_SEGMENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a97f99046a6817e8e15da73f3533317ea</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryConvert)==static_cast&lt; int &gt;(GST_QUERY_CONVERT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6a16d39d17a408551a035f1ca5b0488a</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryFormats)==static_cast&lt; int &gt;(GST_QUERY_FORMATS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4acf380682e8fba530b0b3624193b495</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryBuffering)==static_cast&lt; int &gt;(GST_QUERY_BUFFERING))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa1d3038b90d74b2dd85667ee63d07aa3</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryCustom)==static_cast&lt; int &gt;(GST_QUERY_CUSTOM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8405ca6f8e68ff2f54736ee62bcc9749</anchor>
      <arglist>(static_cast&lt; int &gt;(QueryUri)==static_cast&lt; int &gt;(GST_QUERY_URI))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6f219e9d8ed77ccb2eeb27770a1a7c21</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagReadOnly)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_READONLY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3768cc667e5d92ca4f6a7d50b7d6bdfb</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagPreroll)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_PREROLL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7e1ea0d0b36434be3cd792921017cb87</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagDiscont)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_DISCONT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a70ca4ee5c984d921d90f546d36fd6979</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagInCaps)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_IN_CAPS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7aaf75abf425564469a056d0a8385bad</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagGap)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_GAP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab181c9f1d41a768463dae097aa2a7672</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagDeltaUnit)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_DELTA_UNIT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1572ba475fe4d6bfd88dab4962deca82</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagMedia1)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_MEDIA1))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1b7fa4e1a5bcd972d256ecd8d2714eae</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagMedia2)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_MEDIA2))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5b489ddcf631fd06d226d07af88a70d5</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagMedia3)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_MEDIA3))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6746859f976d2723daaaa68ef30cf0fb</anchor>
      <arglist>(static_cast&lt; int &gt;(BufferFlagLast)==static_cast&lt; int &gt;(GST_BUFFER_FLAG_LAST))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad41b99bb6e80160b81b477bed7978e1b</anchor>
      <arglist>(static_cast&lt; int &gt;(EventTypeUpstream)==static_cast&lt; int &gt;(GST_EVENT_TYPE_UPSTREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae6525b93cf5e372f53b2b4ccaabc3859</anchor>
      <arglist>(static_cast&lt; int &gt;(EventTypeDownstream)==static_cast&lt; int &gt;(GST_EVENT_TYPE_DOWNSTREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5f1874df022c725b2687dd5d5d2fe1f3</anchor>
      <arglist>(static_cast&lt; int &gt;(EventTypeSerialized)==static_cast&lt; int &gt;(GST_EVENT_TYPE_SERIALIZED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad9a873ce519176a0b14f35f0ca0b97b0</anchor>
      <arglist>(static_cast&lt; int &gt;(EventTypeBoth)==static_cast&lt; int &gt;(GST_EVENT_TYPE_BOTH))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5687e7167a58958eab5f84ca1d70b2dc</anchor>
      <arglist>(static_cast&lt; int &gt;(EventUnknown)==static_cast&lt; int &gt;(GST_EVENT_UNKNOWN))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac7ec4cd1d547a01c184f1bbf57045116</anchor>
      <arglist>(static_cast&lt; int &gt;(EventFlushStart)==static_cast&lt; int &gt;(GST_EVENT_FLUSH_START))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af35efb51a4b8bee43f59220cf626f58e</anchor>
      <arglist>(static_cast&lt; int &gt;(EventFlushStop)==static_cast&lt; int &gt;(GST_EVENT_FLUSH_STOP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5acccd06befeb13c8cc0878310332772</anchor>
      <arglist>(static_cast&lt; int &gt;(EventEos)==static_cast&lt; int &gt;(GST_EVENT_EOS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ac6cae63f9a9fa90ba3d6efa2909dd5a5</anchor>
      <arglist>(static_cast&lt; int &gt;(EventNewSegment)==static_cast&lt; int &gt;(GST_EVENT_NEWSEGMENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5438e7eb57394980bc89033ac0599a0d</anchor>
      <arglist>(static_cast&lt; int &gt;(EventTag)==static_cast&lt; int &gt;(GST_EVENT_TAG))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>adf04153fb215f4860d68f8cde3edec3d</anchor>
      <arglist>(static_cast&lt; int &gt;(EventBufferSize)==static_cast&lt; int &gt;(GST_EVENT_BUFFERSIZE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a56bab3d91a9bd9ea9e05a70f8e6611c5</anchor>
      <arglist>(static_cast&lt; int &gt;(EventSinkMessage)==static_cast&lt; int &gt;(GST_EVENT_SINK_MESSAGE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a69a45fd02384f41f4673e2e3ae3accb5</anchor>
      <arglist>(static_cast&lt; int &gt;(EventQos)==static_cast&lt; int &gt;(GST_EVENT_QOS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1b198bddaf86df2c5533488a7f8c1446</anchor>
      <arglist>(static_cast&lt; int &gt;(EventSeek)==static_cast&lt; int &gt;(GST_EVENT_SEEK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ab1f6cda82b5165e87d970aaa79a1d43f</anchor>
      <arglist>(static_cast&lt; int &gt;(EventNavigation)==static_cast&lt; int &gt;(GST_EVENT_NAVIGATION))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a41cce48b5ff7885fc598ceef3410ab4d</anchor>
      <arglist>(static_cast&lt; int &gt;(EventLatency)==static_cast&lt; int &gt;(GST_EVENT_LATENCY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae4911eaec04e3fce3d7815a8d0c24030</anchor>
      <arglist>(static_cast&lt; int &gt;(EventStep)==static_cast&lt; int &gt;(GST_EVENT_STEP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a95663eea3f544110edf422e69059526e</anchor>
      <arglist>(static_cast&lt; int &gt;(EventCustomUpstream)==static_cast&lt; int &gt;(GST_EVENT_CUSTOM_UPSTREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a62638937fd11f31bea28662e157a308d</anchor>
      <arglist>(static_cast&lt; int &gt;(EventCustomDownstream)==static_cast&lt; int &gt;(GST_EVENT_CUSTOM_DOWNSTREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ae2cd1dea81a8b9561975d68f84644b44</anchor>
      <arglist>(static_cast&lt; int &gt;(EventCustomDownstreamOob)==static_cast&lt; int &gt;(GST_EVENT_CUSTOM_DOWNSTREAM_OOB))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2eac32480cc0332746e1001b53ebb352</anchor>
      <arglist>(static_cast&lt; int &gt;(EventCustomBoth)==static_cast&lt; int &gt;(GST_EVENT_CUSTOM_BOTH))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a601b81ffd3c63bb4365858129d2b38e7</anchor>
      <arglist>(static_cast&lt; int &gt;(EventCustomBothOob)==static_cast&lt; int &gt;(GST_EVENT_CUSTOM_BOTH_OOB))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a438fe652445b301bfec583776fb9f2a7</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagNone)==static_cast&lt; int &gt;(GST_SEEK_FLAG_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a57aee25b45a11b77c17435483f13878e</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagFlush)==static_cast&lt; int &gt;(GST_SEEK_FLAG_FLUSH))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a1f68409f946153f7f469aa7a51999ed4</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagAccurate)==static_cast&lt; int &gt;(GST_SEEK_FLAG_ACCURATE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>acb27cec4d6ea5be767690d3b5019983c</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagKeyUnit)==static_cast&lt; int &gt;(GST_SEEK_FLAG_KEY_UNIT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3f7f58932597652a48d1f6d509890f18</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagSegment)==static_cast&lt; int &gt;(GST_SEEK_FLAG_SEGMENT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a36fef7eaaaab109c21c85ff7d18be8f2</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekFlagSkip)==static_cast&lt; int &gt;(GST_SEEK_FLAG_SKIP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a9752eab45ec50c720a59c79dcd86518e</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekTypeNone)==static_cast&lt; int &gt;(GST_SEEK_TYPE_NONE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a79bacddd211c8df26fa494695bc7b256</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekTypeCur)==static_cast&lt; int &gt;(GST_SEEK_TYPE_CUR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0de1f99ff4b9bfdaed1968816a4c6007</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekTypeSet)==static_cast&lt; int &gt;(GST_SEEK_TYPE_SET))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3e931a10ecb9c72f2ea844a5f8ea033d</anchor>
      <arglist>(static_cast&lt; int &gt;(SeekTypeEnd)==static_cast&lt; int &gt;(GST_SEEK_TYPE_END))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a6a8b51e0edc859d9fcbe235f2a129a19</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeUndefined)==static_cast&lt; int &gt;(GST_TAG_MERGE_UNDEFINED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af0ff5212b2b0cbc5c259992d6f214323</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeReplaceAll)==static_cast&lt; int &gt;(GST_TAG_MERGE_REPLACE_ALL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a75ac584d35b2b9ea4e6a8b05c870c18a</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeReplace)==static_cast&lt; int &gt;(GST_TAG_MERGE_REPLACE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0e14259877216006f8137280f8861a5c</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeAppend)==static_cast&lt; int &gt;(GST_TAG_MERGE_APPEND))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aa045fa5866864967ea1c10afd69c26be</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergePrepend)==static_cast&lt; int &gt;(GST_TAG_MERGE_PREPEND))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a105a2e5179f504b23ea7153908516cef</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeKeep)==static_cast&lt; int &gt;(GST_TAG_MERGE_KEEP))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a83304fb04d3b338a2b9c84f8421f9b43</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeKeepAll)==static_cast&lt; int &gt;(GST_TAG_MERGE_KEEP_ALL))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a73129d5bfe8aa664ab401df12a64f488</anchor>
      <arglist>(static_cast&lt; int &gt;(TagMergeCount)==static_cast&lt; int &gt;(GST_TAG_MERGE_COUNT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a80e00dae7170a042aa7e5bbd23b46e7a</anchor>
      <arglist>(static_cast&lt; int &gt;(TagFlagUndefined)==static_cast&lt; int &gt;(GST_TAG_FLAG_UNDEFINED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a37bc8f67c59444894957278dd2070697</anchor>
      <arglist>(static_cast&lt; int &gt;(TagFlagMeta)==static_cast&lt; int &gt;(GST_TAG_FLAG_META))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af96498e62c8a048a782c5767e17255ec</anchor>
      <arglist>(static_cast&lt; int &gt;(TagFlagEncoded)==static_cast&lt; int &gt;(GST_TAG_FLAG_ENCODED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4d765454c393535380892b469e754b77</anchor>
      <arglist>(static_cast&lt; int &gt;(TagFlagDecoded)==static_cast&lt; int &gt;(GST_TAG_FLAG_DECODED))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a0560ef03e5f03eb182810e129f38c709</anchor>
      <arglist>(static_cast&lt; int &gt;(TagFlagCount)==static_cast&lt; int &gt;(GST_TAG_FLAG_COUNT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a857a0e38f79f8ba14bdc89e0ad2f3a56</anchor>
      <arglist>(static_cast&lt; int &gt;(AppStreamTypeStream)==static_cast&lt; int &gt;(GST_APP_STREAM_TYPE_STREAM))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a4cbe89c78dd04abc7ab572e810f8e57c</anchor>
      <arglist>(static_cast&lt; int &gt;(AppStreamTypeSeekable)==static_cast&lt; int &gt;(GST_APP_STREAM_TYPE_SEEKABLE))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a684b080e00d91080f9848c69c1690077</anchor>
      <arglist>(static_cast&lt; int &gt;(AppStreamTypeRandomAccess)==static_cast&lt; int &gt;(GST_APP_STREAM_TYPE_RANDOM_ACCESS))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aafe2f2cd3842e4699acac9356bc837b9</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererOk)==static_cast&lt; int &gt;(GST_DISCOVERER_OK))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a605d071837dc5bf88d937b84b7c8375e</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererUriInvalid)==static_cast&lt; int &gt;(GST_DISCOVERER_URI_INVALID))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a26999c8be2a580f22c4f56e85fc3c0dd</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererError)==static_cast&lt; int &gt;(GST_DISCOVERER_ERROR))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a861368e4918d171f77ed4a5e023d3ce7</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererTimeout)==static_cast&lt; int &gt;(GST_DISCOVERER_TIMEOUT))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a05f8d9bf261f251b39e29a9214a96f38</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererBusy)==static_cast&lt; int &gt;(GST_DISCOVERER_BUSY))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_STATIC_ASSERT</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>aeebd9d154a4100382d177510b7834838</anchor>
      <arglist>(static_cast&lt; int &gt;(DiscovererMissingPlugins)==static_cast&lt; int &gt;(GST_DISCOVERER_MISSING_PLUGINS))</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Caps_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a3e7e42f47f6a0be429382fb3534d6edd</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>PropertyProbe_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a7bfd183f823235402aa2b2f9b43bb502</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>VideoOrientation_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>addce4f079c3be3503a2a90ad7014a9e0</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefCountedObject *</type>
      <name>Query_new</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>afb6bffa68adc17bac8dd9e19bd7e1d07</anchor>
      <arglist>(void *instance)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2be0897834106fd44aeaf44770d03850</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>ad5b9f6bc258eb5b57e619aea3bc16f61</anchor>
      <arglist>(int *argc, char **argv[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>af854931adda54e40b759bf4f736f1cbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a5d1bcd79bd9b6f8e74be4a6732d19bb5</anchor>
      <arglist>(QDebug debug, const Fraction &amp;f)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>acd9f3fde8c66371159d636bcfc6a9814</anchor>
      <arglist>(QDebug debug, const Structure &amp;structure)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getStringTag</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a59833734bbea398ee0d436278b0d9337</anchor>
      <arglist>(GstTagList *list, const gchar *tag, int index)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>getUintTag</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a14a81f6b1a48705d9f16a3f523d9c435</anchor>
      <arglist>(GstTagList *list, const gchar *tag, int index)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getDoubleTag</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a41e6de4e2faaf00c0215c37a2078ba21</anchor>
      <arglist>(GstTagList *list, const gchar *tag, int index)</arglist>
    </member>
    <member kind="function">
      <type>QGst::BufferPtr</type>
      <name>getBufferTag</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a8ac3a4b924fbcd35bc5c19f0f2a1d0e4</anchor>
      <arglist>(GstTagList *list, const gchar *tag, int index)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceQGst.html</anchorfile>
      <anchor>a2d0f07f50d70765278067f83893436b1</anchor>
      <arglist>(QDebug debug, const TagList &amp;taglist)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Bin</name>
    <filename>classQGst_1_1Bin.html</filename>
    <base>QGst::Element</base>
    <base>QGst::ChildProxy</base>
    <member kind="enumeration">
      <name>BinFromDescriptionOption</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a489b5388e7dfd86d09515ab5722e8c30</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NoGhost</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a489b5388e7dfd86d09515ab5722e8c30af7da338d0e56403a6ed00dab8af6c105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Ghost</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a489b5388e7dfd86d09515ab5722e8c30a239509dabd65e2a391edd07e5efc3b77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>RecursionType</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a01cb626950c03ba09d342ab684c55fba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RecurseDown</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a01cb626950c03ba09d342ab684c55fbaacd58538bef7d8914ee87305f167ac0fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RecurseUp</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a01cb626950c03ba09d342ab684c55fbaa708a4aeb728ef49d558ac9960a63307c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>add</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a0db9ee68d5c77fa3323009f90f92005d</anchor>
      <arglist>(const ElementPtr &amp;element)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>ab04e33182b2a5aa16d9fea83df988cfc</anchor>
      <arglist>(const First &amp;first, const Second &amp;second, const Rest &amp;...rest)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>remove</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>ad30af9b2ddd58b53bad3144f28a760fa</anchor>
      <arglist>(const ElementPtr &amp;element)</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>getElementByName</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>ac554c5b2b9d32cd0abcd9ad654ab2fbd</anchor>
      <arglist>(const char *name, RecursionType recursionType=RecurseDown) const </arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>getElementByInterface</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a3984e8838cd8415d5359892839f2977c</anchor>
      <arglist>(QGlib::Type interfaceType) const </arglist>
    </member>
    <member kind="function">
      <type>QGlib::RefPointer&lt; T &gt;</type>
      <name>getElementByInterface</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a98c49074635e40767b916c30d318369e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PadPtr</type>
      <name>findUnlinkedPad</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a6ecbb8a0453211ca7c10a7e38e5ec3e4</anchor>
      <arglist>(PadDirection direction) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>recalculateLatency</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a8630057216b0c16461c9884ebf0954f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BinPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a2061875e41a3658e188f8639cb7e58d5</anchor>
      <arglist>(const char *name=NULL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BinPtr</type>
      <name>fromDescription</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a5a6b3c1d914e6c2ec4d862f4ffcc04b9</anchor>
      <arglist>(const char *description, BinFromDescriptionOption ghostUnlinkedPads=Ghost)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BinPtr</type>
      <name>fromDescription</name>
      <anchorfile>classQGst_1_1Bin.html</anchorfile>
      <anchor>a62e60b307e3029be199829e55ffb4b1c</anchor>
      <arglist>(const QString &amp;description, BinFromDescriptionOption ghostUnlinkedPads=Ghost)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Buffer</name>
    <filename>classQGst_1_1Buffer.html</filename>
    <base>QGst::MiniObject</base>
    <member kind="function">
      <type>quint8 *</type>
      <name>data</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>ab2c14d32bce191d9488f27e24aeb2a9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>size</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a0cb36ade7dbad972c7645a514ce8c67e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>timeStamp</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a6a30cd1e41d8fa45964848b9be10a2c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a13f4893c4d1c4007f75ba5e455c6375b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>caps</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>aa8c7161c1684d30263e01eb954a60abf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCaps</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a83842d8b5c00dfa1647d13943cb21ea4</anchor>
      <arglist>(const CapsPtr &amp;caps)</arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>offset</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>ab353eb523d80a69d6ec3e5a7584af41c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>offsetEnd</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a9e3a020a678081d6dc625edaf38b82e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferFlags</type>
      <name>flags</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>af47a9aaee2bec8ef54e9eb129e90dd48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFlags</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a510091e322535824d6596d46e16fe09c</anchor>
      <arglist>(const BufferFlags flags)</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a5c236f81713b5a41a2b461943180f1ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>makeWritable</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a6ca563c72f61dde3737bc3583e49c6ff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BufferPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1Buffer.html</anchorfile>
      <anchor>a88a7ae40ff11de1e665e66dfc2fead44</anchor>
      <arglist>(uint size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::BufferList</name>
    <filename>classQGst_1_1BufferList.html</filename>
    <base>QGst::MiniObject</base>
    <member kind="function">
      <type>uint</type>
      <name>groupsCount</name>
      <anchorfile>classQGst_1_1BufferList.html</anchorfile>
      <anchor>a270c57a76bd4ca3ed79ffca88b2fa352</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>bufferAt</name>
      <anchorfile>classQGst_1_1BufferList.html</anchorfile>
      <anchor>ac98321a08998a35adc868fe7eb7dd708</anchor>
      <arglist>(uint group, uint index) const </arglist>
    </member>
    <member kind="function">
      <type>BufferListPtr</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1BufferList.html</anchorfile>
      <anchor>a8f10defcb7013e4e19258506480f5549</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferListPtr</type>
      <name>makeWritable</name>
      <anchorfile>classQGst_1_1BufferList.html</anchorfile>
      <anchor>a7e3147ea91cdb9f08d8a1c18f071b6f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BufferListPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1BufferList.html</anchorfile>
      <anchor>a8255faeddd8c5a8d44b38b136515ad70</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::BufferListIterator</name>
    <filename>classQGst_1_1BufferListIterator.html</filename>
    <member kind="function">
      <type></type>
      <name>BufferListIterator</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>ae105b13e3e67644569d83370cbdc84a1</anchor>
      <arglist>(const BufferListPtr &amp;list)</arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>buffersInCurrentGroup</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>a018ddfa4e6371aebddbc3b359b3fdb14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>next</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>a03e9853c5a1a31383ea9587581fbe91d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>aa07de71ae700503da12413d517f6e4f9</anchor>
      <arglist>(const BufferPtr &amp;buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>remove</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>a3f78ef9b92921219b4ed772d25f8115e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>take</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>af8274ea850de1c00b522c03c142459ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>replace</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>aaa3883e1517fd20fdc43abf727bd82db</anchor>
      <arglist>(const BufferPtr &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addGroup</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>ac62cc9a1489225021fbd4bc6a0deafff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nextGroup</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>a99cc3db5517075ad4a3eb31d9ca8fb2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>mergeGroup</name>
      <anchorfile>classQGst_1_1BufferListIterator.html</anchorfile>
      <anchor>af472b3ed36ac91b15f92517e5ad2c6a4</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Bus</name>
    <filename>classQGst_1_1Bus.html</filename>
    <base>QGst::Object</base>
    <member kind="function">
      <type>bool</type>
      <name>post</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a34f791be41e1384411082d8879702fdb</anchor>
      <arglist>(const MessagePtr &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasPendingMessages</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a56e838774023b7321294d48778084a6c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MessagePtr</type>
      <name>peek</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a3f10906b5cd3823acc0d349a8a4503fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MessagePtr</type>
      <name>pop</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a6110aabf6b07d19038b4ae49c37db0dc</anchor>
      <arglist>(ClockTime timeout=0)</arglist>
    </member>
    <member kind="function">
      <type>MessagePtr</type>
      <name>pop</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a3e9a76f0e036da48719cd74a66e748f7</anchor>
      <arglist>(MessageType type, ClockTime timeout=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFlushing</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a690041fe674a0e7a8791f613d4cdc265</anchor>
      <arglist>(bool flush)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addSignalWatch</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a34a7a015e7b5c6b0bb2925ab8489cba3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSignalWatch</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>ab175de3e25c618774041ef3a720d62f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enableSyncMessageEmission</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>a498cb2bdc13021e535239f6132c8bc0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disableSyncMessageEmission</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>ac82278d68bcb38722d7613d0d9ab6e8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BusPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1Bus.html</anchorfile>
      <anchor>ab51e6612dc95a20cf341ebb11ed44b91</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Caps</name>
    <filename>classQGst_1_1Caps.html</filename>
    <base>QGlib::RefCountedObject</base>
    <member kind="function">
      <type>QString</type>
      <name>toString</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a1e0312c2dac42e7726dea00aaaec4b4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>append</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>af0fffe40453beddcddf5559f3fff0c59</anchor>
      <arglist>(const CapsPtr &amp;caps2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>merge</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a1bc43d6fc697706e92e25f42e496fc29</anchor>
      <arglist>(const CapsPtr &amp;caps2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a0e89bf28657181e7498c3d285580187e</anchor>
      <arglist>(const char *field, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a6503b36aad61c41032901ba49f3e1d0c</anchor>
      <arglist>(const char *field, const QGlib::Value &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>simplify</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a17bcf0f2cdd517764e66280e797ad993</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>truncate</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>aa646b5a1a34a7b508be75768f81dd6ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>StructurePtr</type>
      <name>internalStructure</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a870f5a8de9d21bc008fb623b7ac7413c</anchor>
      <arglist>(uint index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>appendStructure</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>ac86130fb928b929765d937fca6bc4f9b</anchor>
      <arglist>(const Structure &amp;structure)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mergeStructure</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>aed648cd71120b8101d73b3b73c7437a1</anchor>
      <arglist>(const Structure &amp;structure)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeStructure</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a41b4b220c08d57bf660426cb81e96fa1</anchor>
      <arglist>(uint index)</arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>size</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a35f3c28e8d77857bce8ed44ff4fabfd3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSimple</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a7fce4d1f4287ef7424fd508b14b1ca13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAny</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a520fffb0fe6d89605722ae041a38de99</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a064910dc8d7e03ac06347a335c3d06be</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFixed</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a929dd2e3bdcda6d65ea5e85c8c5412ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>equals</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a11cfd94eeeae520792716b1c1daeda7c</anchor>
      <arglist>(const CapsPtr &amp;caps2) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAlwaysCompatibleWith</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a12b6f9113eb6c76db01951dffb244d6e</anchor>
      <arglist>(const CapsPtr &amp;caps2) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSubsetOf</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a34bdef1e4742b62499250de4b223a215</anchor>
      <arglist>(const CapsPtr &amp;superset) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canIntersect</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a704498253ab17811a2956655586c47ff</anchor>
      <arglist>(const CapsPtr &amp;caps2) const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>getIntersection</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a6605e372be217c6c7474f4585894ca2d</anchor>
      <arglist>(const CapsPtr &amp;caps2) const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>getUnion</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a4dfbda2d0f0652fd29b2ef825605864d</anchor>
      <arglist>(const CapsPtr &amp;caps2) const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>getNormal</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>aec5f325265c9d5a9605699a3fa342058</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>subtract</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>acc14937add8121dcb0c9c517a1104b48</anchor>
      <arglist>(const CapsPtr &amp;subtrahend) const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a644af65be0bbceeee133882328969e2d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>copyNth</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a64e0d68ee4d905dc16241b785154b2be</anchor>
      <arglist>(uint index) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isWritable</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a9b4fdf547a6eb7524a452f64af498627</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>makeWritable</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a75e2a94e353ec99e2b8203ce4aea0d3f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CapsPtr</type>
      <name>createSimple</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a12bcfc81c84d20fef85c3c4dd6d3a1dc</anchor>
      <arglist>(const char *mediaType)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CapsPtr</type>
      <name>createAny</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>ae0708f67585dae9053d6c2fe5dc7cd12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CapsPtr</type>
      <name>createEmpty</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a56ae647611a860cde34495d844863225</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CapsPtr</type>
      <name>fromString</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a9df9a66fc01f629c729897623be148ae</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CapsPtr</type>
      <name>fromString</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a62477c91917bb9bd18a1902ddfa64ea4</anchor>
      <arglist>(const QString &amp;string)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a78060b44e59c26d1727b3ec20833067a</anchor>
      <arglist>(bool increaseRef)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>a3c166a5b833236b3897cb50af8e4a17e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classQGst_1_1Caps.html</anchorfile>
      <anchor>abc5eb75b5a65a6a9ca822c26b0e53510</anchor>
      <arglist>(QDebug debug, const CapsPtr &amp;caps)</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>QGst::ChildProxy</name>
    <filename>classQGst_1_1ChildProxy.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>uint</type>
      <name>childrenCount</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>a7b835755193e2ce6821cee10155ca2bf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ObjectPtr</type>
      <name>childByName</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>a2e33e373fab1847d5993aa26c7f47094</anchor>
      <arglist>(const char *name) const </arglist>
    </member>
    <member kind="function">
      <type>ObjectPtr</type>
      <name>childByIndex</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>af96285b9b27348c71533d796a0c921e7</anchor>
      <arglist>(uint index) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>findChildProperty</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>a0c649723408b1da6a9573f856726172f</anchor>
      <arglist>(const char *name, ObjectPtr *object, QGlib::ParamSpecPtr *paramSpec) const </arglist>
    </member>
    <member kind="function">
      <type>QGlib::Value</type>
      <name>childProperty</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>a2dda7839980b8ad0f82f52d408f21ff2</anchor>
      <arglist>(const char *name) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setChildProperty</name>
      <anchorfile>classQGst_1_1ChildProxy.html</anchorfile>
      <anchor>aca54fc701d324bc95a215b58260160e2</anchor>
      <arglist>(const char *name, const T &amp;value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Clock</name>
    <filename>classQGst_1_1Clock.html</filename>
    <base>QGst::Object</base>
    <member kind="function">
      <type>ClockTime</type>
      <name>resolution</name>
      <anchorfile>classQGst_1_1Clock.html</anchorfile>
      <anchor>ad86001963fda8ca585d8fba39262b4a6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>clockTime</name>
      <anchorfile>classQGst_1_1Clock.html</anchorfile>
      <anchor>a92d5bf714e41875258aa06595c5661e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QTime</type>
      <name>time</name>
      <anchorfile>classQGst_1_1Clock.html</anchorfile>
      <anchor>ac01bf99b5fa45fe3fb139c41e95e811c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockPtr</type>
      <name>systemClock</name>
      <anchorfile>classQGst_1_1Clock.html</anchorfile>
      <anchor>a2046e366c14bdca12df81b1a1fe717c4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ClockTime</name>
    <filename>classQGst_1_1ClockTime.html</filename>
    <member kind="function">
      <type></type>
      <name>ClockTime</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>adafdd4e2499ffd5dd774593cf4c5d54c</anchor>
      <arglist>(quint64 t=None)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator quint64</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a30c49023de9fb1f06391b11a2367a482</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a129d848c6883b0417dee21c5e15517dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QTime</type>
      <name>toTime</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a91d691fb5fde1e3f50d2087c4bbb6ac6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>fromTime</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a3f2b1452ddfde1453d987e1e6908b079</anchor>
      <arglist>(const QTime &amp;time)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>fromSeconds</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>ad735dc6e0541fd07c9dfbfcb7120e3df</anchor>
      <arglist>(quint64 seconds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>fromMSecs</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a654a8b9f07a9ce822b6332cfcfa904e1</anchor>
      <arglist>(quint64 msec)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>fromUSecs</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a3061401b42219fa2229695e835be4822</anchor>
      <arglist>(quint64 usec)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const quint64</type>
      <name>None</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a62b635b5f5caf515656a16e8fded299a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>qint64</type>
      <name>ClockTimeDiff</name>
      <anchorfile>classQGst_1_1ClockTime.html</anchorfile>
      <anchor>a80fb00a11f00bbec5a3e95e8f12b88c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ColorBalanceChannel</name>
    <filename>classQGst_1_1ColorBalanceChannel.html</filename>
    <base>QGlib::Object</base>
    <member kind="function">
      <type>QString</type>
      <name>label</name>
      <anchorfile>classQGst_1_1ColorBalanceChannel.html</anchorfile>
      <anchor>a189ac442fc2e6f99873ae03037918db8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>minValue</name>
      <anchorfile>classQGst_1_1ColorBalanceChannel.html</anchorfile>
      <anchor>a77448a7c4d07d521e3094d705f1b2aa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>maxValue</name>
      <anchorfile>classQGst_1_1ColorBalanceChannel.html</anchorfile>
      <anchor>a11b9c56e5f02cf48d0547257a561e6c4</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ColorBalance</name>
    <filename>classQGst_1_1ColorBalance.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>ColorBalanceType</type>
      <name>type</name>
      <anchorfile>classQGst_1_1ColorBalance.html</anchorfile>
      <anchor>a4452f5d7544af88c50001e7002a31ada</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; ColorBalanceChannelPtr &gt;</type>
      <name>channels</name>
      <anchorfile>classQGst_1_1ColorBalance.html</anchorfile>
      <anchor>af1850c0bd556fd4f694cdfe8d3ac4344</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>value</name>
      <anchorfile>classQGst_1_1ColorBalance.html</anchorfile>
      <anchor>a5ca2de80c4e4e55689b4ffe966cc51f4</anchor>
      <arglist>(const ColorBalanceChannelPtr &amp;channel) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classQGst_1_1ColorBalance.html</anchorfile>
      <anchor>ae506878a6a907626dee651e93d24518d</anchor>
      <arglist>(const ColorBalanceChannelPtr &amp;channel, int value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Element</name>
    <filename>classQGst_1_1Element.html</filename>
    <base>QGst::Object</base>
    <member kind="function">
      <type>State</type>
      <name>currentState</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a675d2e3b6967342f8778a39b8eee70a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>State</type>
      <name>pendingState</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a9c35a515fdd9077037f1ae218b77cfe6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>StateChangeReturn</type>
      <name>getState</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a0cc35a3a3c59f13a370766ba51d7ea06</anchor>
      <arglist>(State *state, State *pending, ClockTime timeout) const </arglist>
    </member>
    <member kind="function">
      <type>StateChangeReturn</type>
      <name>setState</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a40b996e48f169e98f71909681ccf9d9b</anchor>
      <arglist>(State state)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>syncStateWithParent</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a5941864b9dd13d4a66c0b0498bf2b5b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stateIsLocked</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a3a416d8ce4b3a8debff6fb9725bd8afc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setStateLocked</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a9efa0dcaafb9eee7e94ae28b52a617ad</anchor>
      <arglist>(bool locked)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>addPad</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>aabec4870411bcdab821504a84554e7fb</anchor>
      <arglist>(const PadPtr &amp;pad)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>removePad</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a35202dbd0b912890249675cd8f8b509d</anchor>
      <arglist>(const PadPtr &amp;pad)</arglist>
    </member>
    <member kind="function">
      <type>PadPtr</type>
      <name>getStaticPad</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a52dd2ec4de6b811ec411cd8d4c70550c</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>PadPtr</type>
      <name>getRequestPad</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>ab9bad5f3a1e2cbc1ffb1790524dfb289</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>releaseRequestPad</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a173ed35879e81f17823474d808ed9248</anchor>
      <arglist>(const PadPtr &amp;pad)</arglist>
    </member>
    <member kind="function">
      <type>ClockPtr</type>
      <name>clock</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>aa80f86222c29c7fa5b96fbf01ded7b31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setClock</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a684589657758af30352e94cf64fc78d2</anchor>
      <arglist>(const ClockPtr &amp;clock)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>link</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>ac153c03190ff0aa2d461fb3c3d963ab0</anchor>
      <arglist>(const char *srcPadName, const ElementPtr &amp;dest, const char *sinkPadName, const CapsPtr &amp;filter=CapsPtr())</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>link</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a9957cb6e573fbd07f6a303b117737062</anchor>
      <arglist>(const char *srcPadName, const ElementPtr &amp;dest, const CapsPtr &amp;filter=CapsPtr())</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>link</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a55892fdd17d1f932e27a22c54d7d8916</anchor>
      <arglist>(const ElementPtr &amp;dest, const char *sinkPadName, const CapsPtr &amp;filter=CapsPtr())</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>link</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>aa1fbef4e7001f06b69bd4346ff9876e9</anchor>
      <arglist>(const ElementPtr &amp;dest, const CapsPtr &amp;filter=CapsPtr())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unlink</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a493c8acad5817481f82257c49848c0d2</anchor>
      <arglist>(const char *srcPadName, const ElementPtr &amp;dest, const char *sinkPadName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unlink</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>ab83920777c22b78e2d64c5ebe91b0554</anchor>
      <arglist>(const ElementPtr &amp;dest)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>query</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a24cc0fe95d7e711ee8f25ab5a847b348</anchor>
      <arglist>(const QueryPtr &amp;query)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sendEvent</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a117caff9769c0e05e2de1a707686275f</anchor>
      <arglist>(const EventPtr &amp;event)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>seek</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a00c361366d876473fd1442d51da69333</anchor>
      <arglist>(Format format, SeekFlags flags, quint64 position)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>linkMany</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>aeb5904f99d0d52183b669a9a7ac3c769</anchor>
      <arglist>(const First &amp;first, const Second &amp;second, const Third &amp;third, const Rest &amp;...rest)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>unlinkMany</name>
      <anchorfile>classQGst_1_1Element.html</anchorfile>
      <anchor>a7a8dec23109ec53f0494f230e981460b</anchor>
      <arglist>(const First &amp;first, const Second &amp;second, const Third &amp;third, const Rest &amp;...rest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ElementFactory</name>
    <filename>classQGst_1_1ElementFactory.html</filename>
    <base>QGst::PluginFeature</base>
    <member kind="function">
      <type>QGlib::Type</type>
      <name>elementType</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a19838ba5579ab895d37dbdd0c9f52e96</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>longName</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a92fe1a20c0e8f620c61c50467d932446</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>klass</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a8008f2564a5c20fe63a47304005d0a0c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>description</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>afa9fbbb749e0ed52c7be3414b255fbdc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>author</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a27f40203c548f019a5eb7efdeabc0e95</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>documentationUri</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a8c623b898f44cd6dd4b54ec9031b450b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>iconName</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a35da81519e6ef64fd4f86ba9cd55b46e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>padTemplatesCount</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a4e55b290c5e14835d15918ed55c777fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>uriType</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>adc98e2cd36a6969147b7a93d8259f822</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasInterface</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a952db5eb6df900de8296d680c7129ed1</anchor>
      <arglist>(const char *interfaceName) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canSinkCaps</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a9bc1e7e6650231d0bdf21c1a82e18ec5</anchor>
      <arglist>(const CapsPtr &amp;caps) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canSrcCaps</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>af84a98f4e76d446421f0eeb0996945a8</anchor>
      <arglist>(const CapsPtr &amp;caps) const </arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>ab9bc7fe2cf14b825333ab9768fb7c431</anchor>
      <arglist>(const char *elementName=NULL) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ElementFactoryPtr</type>
      <name>find</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a5b919a4beb7b6a8c450b8647d1df52f4</anchor>
      <arglist>(const char *factoryName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ElementFactoryPtr</type>
      <name>find</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a1054986438fdc6b48a4b7083b12cffce</anchor>
      <arglist>(const QString &amp;factoryName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ElementPtr</type>
      <name>make</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>a24edb80b14b2471365bcf853c76150a8</anchor>
      <arglist>(const char *factoryName, const char *elementName=NULL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ElementPtr</type>
      <name>make</name>
      <anchorfile>classQGst_1_1ElementFactory.html</anchorfile>
      <anchor>aac867a6b21d0fa596ced84b5d826ddaf</anchor>
      <arglist>(const QString &amp;factoryName, const char *elementName=NULL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Event</name>
    <filename>classQGst_1_1Event.html</filename>
    <base>QGst::MiniObject</base>
    <member kind="function">
      <type>ObjectPtr</type>
      <name>source</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>affdc81612dcc03df1aa80405ea530c88</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>timestamp</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>ab72a4c064ea66c0b3079869d8d30ac58</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>EventType</type>
      <name>type</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>a09b15cd79b2e817d59c6f4b3b7ed9e55</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>typeName</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>a5aa515499f60fd6b32f03be0ff3c5aa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>StructurePtr</type>
      <name>internalStructure</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>a5c9f498824dbdd7c25cf26b24da0a270</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>sequenceNumber</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>a5f60e3c57a2b3508fc8ca298bec08236</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSequenceNumber</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>ab3f6817c6bdb71adb1dc718f32a1dbee</anchor>
      <arglist>(quint32 num)</arglist>
    </member>
    <member kind="function">
      <type>EventPtr</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1Event.html</anchorfile>
      <anchor>af11069740180e31f8302d09f9efbe70e</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::FlushStartEvent</name>
    <filename>classQGst_1_1FlushStartEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function" static="yes">
      <type>static FlushStartEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1FlushStartEvent.html</anchorfile>
      <anchor>a4d8f200c9c028078b35bdb94311ca443</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::FlushStopEvent</name>
    <filename>classQGst_1_1FlushStopEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function" static="yes">
      <type>static FlushStopEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1FlushStopEvent.html</anchorfile>
      <anchor>aaf6f569b15920c0d6554be8e21a6eea1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::EosEvent</name>
    <filename>classQGst_1_1EosEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function" static="yes">
      <type>static EosEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1EosEvent.html</anchorfile>
      <anchor>ab8a8d1813ca9aa42afa5ba92639d7454</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::NewSegmentEvent</name>
    <filename>classQGst_1_1NewSegmentEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>bool</type>
      <name>isUpdate</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>a36ccdceca793ca11eac06de11bdb84f4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>acbcd3b4f9853f52e43d01dda7f28f3e5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>appliedRate</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>a6ccf5989614d104b46fe0e94f0ae495a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>af64ef6c20b49dd01706eed805900d91c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>start</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>aef797af4bee6c81e84c0c28dacdb9059</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>stop</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>a3ebe50244c3a644da76eb6d9764165ac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>position</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>a466ab11420b2868e03b9880cd7fdc51b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static NewSegmentEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1NewSegmentEvent.html</anchorfile>
      <anchor>ae5a40fd4ce3f8b626a06fcee25140dae</anchor>
      <arglist>(bool update, double rate, double appliedRate, Format format, qint64 start, qint64 stop, qint64 position)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::TagEvent</name>
    <filename>classQGst_1_1TagEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>TagList</type>
      <name>taglist</name>
      <anchorfile>classQGst_1_1TagEvent.html</anchorfile>
      <anchor>a6c54d85add747abde7283527a9cefb4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static TagEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1TagEvent.html</anchorfile>
      <anchor>aaa66010430997f9d492c348ee295a98b</anchor>
      <arglist>(const TagList &amp;taglist)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::BufferSizeEvent</name>
    <filename>classQGst_1_1BufferSizeEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1BufferSizeEvent.html</anchorfile>
      <anchor>a2c583d7c03a23572fb9a7da579731796</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>minSize</name>
      <anchorfile>classQGst_1_1BufferSizeEvent.html</anchorfile>
      <anchor>af62c5afbb630227371cb1d218f0313ad</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>maxSize</name>
      <anchorfile>classQGst_1_1BufferSizeEvent.html</anchorfile>
      <anchor>acf0e7929b0d7e4e6e6056e56e8c22cbf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAsync</name>
      <anchorfile>classQGst_1_1BufferSizeEvent.html</anchorfile>
      <anchor>a55be0760035b6e38510534f83152d34f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BufferSizeEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1BufferSizeEvent.html</anchorfile>
      <anchor>a0cce957a53a3e8ba57a57b0fd0c6ed69</anchor>
      <arglist>(Format format, qint64 minSize, qint64 maxSize, bool isAsync)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SinkMessageEvent</name>
    <filename>classQGst_1_1SinkMessageEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>MessagePtr</type>
      <name>message</name>
      <anchorfile>classQGst_1_1SinkMessageEvent.html</anchorfile>
      <anchor>a8402eae5d2d583899818461751386c39</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SinkMessageEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1SinkMessageEvent.html</anchorfile>
      <anchor>a4688a9371fbc3ffd5b28117351dd0111</anchor>
      <arglist>(const MessagePtr &amp;msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::QosEvent</name>
    <filename>classQGst_1_1QosEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>double</type>
      <name>proportion</name>
      <anchorfile>classQGst_1_1QosEvent.html</anchorfile>
      <anchor>adf3471c99c8c21d4f4ec362f1682fc2b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTimeDiff</type>
      <name>diff</name>
      <anchorfile>classQGst_1_1QosEvent.html</anchorfile>
      <anchor>a9ee28b9fae12c4051e07cc2bdc22ddd7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>timestamp</name>
      <anchorfile>classQGst_1_1QosEvent.html</anchorfile>
      <anchor>acf0e2019d55048af98d10edb13f7c223</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QosEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1QosEvent.html</anchorfile>
      <anchor>a5268ee9a6efe0c6e2563530b183a8a95</anchor>
      <arglist>(double proportion, ClockTimeDiff diff, ClockTime timestamp)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SeekEvent</name>
    <filename>classQGst_1_1SeekEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>a3cb0bea2a4d512bd81af8b7309750826</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>ae8499e2947dc95521560e7c5065b476f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SeekFlags</type>
      <name>flags</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>ac3adbd69ee86beede28ca013f1782067</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SeekType</type>
      <name>startType</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>a9f71397109075a08b80f67b588fe609d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>start</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>a576ac4153472c9a7ff0bef17264f85ca</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>SeekType</type>
      <name>stopType</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>abb2c1470a7582fd970be0f3ee773fa76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>stop</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>a257ce8222912a82836154ca90e2b5d50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SeekEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1SeekEvent.html</anchorfile>
      <anchor>aa54ad9f9a67deee49faad73f69450758</anchor>
      <arglist>(double rate, Format format, SeekFlags flags, SeekType startType, qint64 start, SeekType stopType, qint64 stop)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::NavigationEvent</name>
    <filename>classQGst_1_1NavigationEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function" static="yes">
      <type>static NavigationEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1NavigationEvent.html</anchorfile>
      <anchor>a791a8e980d0a8df70cc28d0a199c5535</anchor>
      <arglist>(const Structure &amp;structure=Structure())</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::LatencyEvent</name>
    <filename>classQGst_1_1LatencyEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>ClockTime</type>
      <name>latency</name>
      <anchorfile>classQGst_1_1LatencyEvent.html</anchorfile>
      <anchor>af3839e78a7248ac6884dd59c2d1fc379</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static LatencyEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1LatencyEvent.html</anchorfile>
      <anchor>a2dc48f20e46ec14c7729432c224f8e28</anchor>
      <arglist>(ClockTime latency)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StepEvent</name>
    <filename>classQGst_1_1StepEvent.html</filename>
    <base>QGst::Event</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>a3be4dab073dcdc52a5629c06f7b8a6ee</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>amount</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>a5f6b97b99182f8852f58071680712537</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>a2a54bd954464fb9ecf9cc249a8ce30b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flush</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>a60a1edd688615d8ace31a93090bef9ed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>intermediate</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>af816b19266d5ff75f38f90c7484b24de</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static StepEventPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1StepEvent.html</anchorfile>
      <anchor>a986e4e1a6e175c001ec942152d408d35</anchor>
      <arglist>(Format format, quint64 amount, double rate, bool flush, bool intermediate)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::GhostPad</name>
    <filename>classQGst_1_1GhostPad.html</filename>
    <base>QGst::Pad</base>
    <member kind="function">
      <type>PadPtr</type>
      <name>target</name>
      <anchorfile>classQGst_1_1GhostPad.html</anchorfile>
      <anchor>a4a4ad985852489826371730165a6d00f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setTarget</name>
      <anchorfile>classQGst_1_1GhostPad.html</anchorfile>
      <anchor>ac74dae722dc70e7b04eb8beb3925eb6b</anchor>
      <arglist>(const PadPtr &amp;target)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GhostPadPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1GhostPad.html</anchorfile>
      <anchor>a311cc02c7b796c027bb27c950c361f21</anchor>
      <arglist>(const PadPtr &amp;target, const char *name=NULL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GhostPadPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1GhostPad.html</anchorfile>
      <anchor>a028be51cbb916f491a638dd743dd6c3f</anchor>
      <arglist>(PadDirection direction, const char *name=NULL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Message</name>
    <filename>classQGst_1_1Message.html</filename>
    <base>QGst::MiniObject</base>
    <member kind="function">
      <type>ObjectPtr</type>
      <name>source</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>a824e8221bf0f4543a1f0acd599898d6b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>timestamp</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>a5d75d69edcb95c9dc90a3fc04601a521</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>typeName</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>a87722234ea09756443be35653ad5f3f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MessageType</type>
      <name>type</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>a29b4a0ffa82cec50bd9d401de2d1be59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>StructurePtr</type>
      <name>internalStructure</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>a589b582f12dc26b431072eaf81293c2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>sequenceNumber</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>ab6ab5d3404110a016af63145e84ee73c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSequenceNumber</name>
      <anchorfile>classQGst_1_1Message.html</anchorfile>
      <anchor>ae7c81b99cc1cc5c7330c0284ce115dab</anchor>
      <arglist>(quint32 num)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::EosMessage</name>
    <filename>classQGst_1_1EosMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function" static="yes">
      <type>static EosMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1EosMessage.html</anchorfile>
      <anchor>ab4678b7ad1729bd3f3c56696e3bbab10</anchor>
      <arglist>(const ObjectPtr &amp;source)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ErrorMessage</name>
    <filename>classQGst_1_1ErrorMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>QGlib::Error</type>
      <name>error</name>
      <anchorfile>classQGst_1_1ErrorMessage.html</anchorfile>
      <anchor>ad5a70a2355f0e178c12df3ac76ed443b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>debugMessage</name>
      <anchorfile>classQGst_1_1ErrorMessage.html</anchorfile>
      <anchor>a8b7a2c3387f7a0ef959a794d1f18793e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ErrorMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1ErrorMessage.html</anchorfile>
      <anchor>af5a92bcc3535cf3868f9cc0206448b87</anchor>
      <arglist>(const ObjectPtr &amp;source, const QGlib::Error &amp;error, const char *debug)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::WarningMessage</name>
    <filename>classQGst_1_1WarningMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>QGlib::Error</type>
      <name>error</name>
      <anchorfile>classQGst_1_1WarningMessage.html</anchorfile>
      <anchor>a30ec43872d4a2aeb36af7dc3c5c3f83d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>debugMessage</name>
      <anchorfile>classQGst_1_1WarningMessage.html</anchorfile>
      <anchor>ad9bee972bba65ba317903fcb59546759</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static WarningMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1WarningMessage.html</anchorfile>
      <anchor>a0dc800a3e379dc8bd19f4c838df22d44</anchor>
      <arglist>(const ObjectPtr &amp;source, const QGlib::Error &amp;error, const char *debug)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::InfoMessage</name>
    <filename>classQGst_1_1InfoMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>QGlib::Error</type>
      <name>error</name>
      <anchorfile>classQGst_1_1InfoMessage.html</anchorfile>
      <anchor>a58d6ae7b8bdde6e8864c58f80201c0e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>debugMessage</name>
      <anchorfile>classQGst_1_1InfoMessage.html</anchorfile>
      <anchor>a62ccf4cb15f90ec9a1eee897e7b65688</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static InfoMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1InfoMessage.html</anchorfile>
      <anchor>a73867193337950b06934945a2717c420</anchor>
      <arglist>(const ObjectPtr &amp;source, const QGlib::Error &amp;error, const char *debug)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::TagMessage</name>
    <filename>classQGst_1_1TagMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>TagList</type>
      <name>taglist</name>
      <anchorfile>classQGst_1_1TagMessage.html</anchorfile>
      <anchor>a22680bda77f9f7532e89def859195dfc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static TagMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1TagMessage.html</anchorfile>
      <anchor>a0a0775998215aef2480ddc6579d39e37</anchor>
      <arglist>(const ObjectPtr &amp;source, const TagList &amp;taglist)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::BufferingMessage</name>
    <filename>classQGst_1_1BufferingMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>int</type>
      <name>percent</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>a197f73f1fbbc665d8d08ad75316f49da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferingMode</type>
      <name>mode</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>a95c587ab15491e961d921de33238981c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>averageInputRate</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>a3d4d0cac6bb8d60a881401ecc37616e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>averageOutputRate</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>a75c73ef9a2c725e4533b350ee28fb3f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>bufferingTimeLeft</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>ab8a6d0694e63deb485c41764511bf85a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStats</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>affd6a7bbc25267c7ccd16262d6d80e70</anchor>
      <arglist>(BufferingMode mode, int avgIn, int avgOut, qint64 bufferingLeft)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BufferingMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1BufferingMessage.html</anchorfile>
      <anchor>a7db7555b91fe88f2d70ef92f82603fe4</anchor>
      <arglist>(const ObjectPtr &amp;source, int percent)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StateChangedMessage</name>
    <filename>classQGst_1_1StateChangedMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>State</type>
      <name>oldState</name>
      <anchorfile>classQGst_1_1StateChangedMessage.html</anchorfile>
      <anchor>ad254ff4ad0e1cd4ef3795265b4e5f968</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>State</type>
      <name>newState</name>
      <anchorfile>classQGst_1_1StateChangedMessage.html</anchorfile>
      <anchor>ad815c754376f0daf7a8fb2d0e2fa33b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>State</type>
      <name>pendingState</name>
      <anchorfile>classQGst_1_1StateChangedMessage.html</anchorfile>
      <anchor>a61a8768ba775d2989ad8b5eeceb5df31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static StateChangedMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1StateChangedMessage.html</anchorfile>
      <anchor>a1242b50096d01e68eeeee5d78b57ef98</anchor>
      <arglist>(const ObjectPtr &amp;source, State oldState, State newState, State pending)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StepDoneMessage</name>
    <filename>classQGst_1_1StepDoneMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>a072769ed93d5503b32c10e9ea17c184e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>amount</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>abf07bb3a56ec97fdaadcc2156894ab48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>a201e58ad65af8ff70f1d69282505ce9c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFlushingStep</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>ad505d0f29e2d776e062bdd56ba53b7b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isIntermediateStep</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>a4fe286758409d0f1c82664e11fab4f49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>af004e5576300d38ac900d685a029359f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>causedEos</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>a5eeb7bd7ade21af3b2590ad18e149c13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static StepDoneMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1StepDoneMessage.html</anchorfile>
      <anchor>a402d8cf0a9af11485772749e65c326b8</anchor>
      <arglist>(const ObjectPtr &amp;source, Format format, quint64 amount, double rate, bool flush, bool intermediate, quint64 duration, bool eos)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StreamStatusMessage</name>
    <filename>classQGst_1_1StreamStatusMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>StreamStatusType</type>
      <name>statusType</name>
      <anchorfile>classQGst_1_1StreamStatusMessage.html</anchorfile>
      <anchor>a8fee57c8a33f95aa2f81c2e35064ea8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>owner</name>
      <anchorfile>classQGst_1_1StreamStatusMessage.html</anchorfile>
      <anchor>ac619704855fb1d1adeaa8e73c5a0353e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QGlib::Value</type>
      <name>streamStatusObject</name>
      <anchorfile>classQGst_1_1StreamStatusMessage.html</anchorfile>
      <anchor>a2fa1ea77da4e84920d699473820162a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStreamStatusObject</name>
      <anchorfile>classQGst_1_1StreamStatusMessage.html</anchorfile>
      <anchor>a0adc63d76072fd7514d93b771c8d4942</anchor>
      <arglist>(const QGlib::Value &amp;object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static StreamStatusMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1StreamStatusMessage.html</anchorfile>
      <anchor>af4820f90c8158dcee7b1a3cd6acded64</anchor>
      <arglist>(const ObjectPtr &amp;source, StreamStatusType type, const ElementPtr &amp;owner)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ApplicationMessage</name>
    <filename>classQGst_1_1ApplicationMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function" static="yes">
      <type>static ApplicationMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1ApplicationMessage.html</anchorfile>
      <anchor>a5e4189b46def1f7a13b2b7e5d7ede987</anchor>
      <arglist>(const ObjectPtr &amp;source, const Structure &amp;structure=Structure())</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ElementMessage</name>
    <filename>classQGst_1_1ElementMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function" static="yes">
      <type>static ElementMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1ElementMessage.html</anchorfile>
      <anchor>adbf43c2699960a35839bcef83e805516</anchor>
      <arglist>(const ObjectPtr &amp;source, const Structure &amp;structure=Structure())</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SegmentDoneMessage</name>
    <filename>classQGst_1_1SegmentDoneMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1SegmentDoneMessage.html</anchorfile>
      <anchor>a66daeb76dcce85adeb9127a30d1c4701</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>position</name>
      <anchorfile>classQGst_1_1SegmentDoneMessage.html</anchorfile>
      <anchor>a9bb659ebf6839f9508b99b4578d55c89</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SegmentDoneMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1SegmentDoneMessage.html</anchorfile>
      <anchor>a92ae88f2eb65ee49e4df720b062d572d</anchor>
      <arglist>(const ObjectPtr &amp;source, Format format, qint64 position)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::DurationMessage</name>
    <filename>classQGst_1_1DurationMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1DurationMessage.html</anchorfile>
      <anchor>aa7276296caaf3fb79dfa96fc333979c5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1DurationMessage.html</anchorfile>
      <anchor>a493f6e290c1d3194674e210b979e27d1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static DurationMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1DurationMessage.html</anchorfile>
      <anchor>a7771142c060c34606742e73b3a1aea76</anchor>
      <arglist>(const ObjectPtr &amp;source, Format format, qint64 duration)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::LatencyMessage</name>
    <filename>classQGst_1_1LatencyMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function" static="yes">
      <type>static LatencyMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1LatencyMessage.html</anchorfile>
      <anchor>a02abcd83fc1bdfce2385f903e1f73460</anchor>
      <arglist>(const ObjectPtr &amp;source)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::AsyncDoneMessage</name>
    <filename>classQGst_1_1AsyncDoneMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function" static="yes">
      <type>static AsyncDoneMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1AsyncDoneMessage.html</anchorfile>
      <anchor>ad7f87f4ea3a121fbdb3f1689caef028e</anchor>
      <arglist>(const ObjectPtr &amp;source)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::RequestStateMessage</name>
    <filename>classQGst_1_1RequestStateMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>State</type>
      <name>state</name>
      <anchorfile>classQGst_1_1RequestStateMessage.html</anchorfile>
      <anchor>a810a5f35b2427b2e6c9e144a4f8c8e4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static RequestStateMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1RequestStateMessage.html</anchorfile>
      <anchor>ab32213ce508df040918707ef272a4cd4</anchor>
      <arglist>(const ObjectPtr &amp;source, State state)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StepStartMessage</name>
    <filename>classQGst_1_1StepStartMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a0f9e6a20efba2b66c8e637ad339078b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a49d9d3effe50db71b049b71129fe1b0a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>amount</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a63a86e0bc666cb413a99d9ac327d5895</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a64a995abb85eb8d1726d3d55aa94f3e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFlushingStep</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a6546fea50a6d00e3204585ced31f903d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isIntermediateStep</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>ada1fa3937e9fb8b698793bce69eaa80d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static StepStartMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1StepStartMessage.html</anchorfile>
      <anchor>a8ed51429c7313ae7ee79a3f520dda254</anchor>
      <arglist>(const ObjectPtr &amp;source, bool active, Format format, quint64 amount, double rate, bool flush, bool intermediate)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::QosMessage</name>
    <filename>classQGst_1_1QosMessage.html</filename>
    <base>QGst::Message</base>
    <member kind="function">
      <type>bool</type>
      <name>live</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a035c250d8979b1176d57956ff7560a12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>runningTime</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a7331e44f38e665a45ae4e12f33813e7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>streamTime</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>ae98b2d569dde593077af94aaea7da7d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>timestamp</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>af19c284bbd36c56a7a8ca196887f241d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>ac801643891735b1d73b30bef62538f81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>jitter</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>ab126d15b3e7103c0c8690c71ff1e99ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>proportion</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a54744279147d862d7fb84f9b79b1fd5e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>quality</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a76c8f7d9b88bc2a386ff37058a9324cd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a6739073af9eba3e461cdcbdebb28bd27</anchor>
      <arglist>(qint64 jitter, double proportion, int quality)</arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a7ff99ecce9889a66e9ff717091d95577</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>processed</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a7f20421135514ccc6c61d465f6489b5c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>dropped</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>ad361f4b3a566b83530786d37cf7bfccb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStats</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>afd3f4eb66935c8c2773d94513e9b5ee5</anchor>
      <arglist>(Format format, quint64 processed, quint64 dropped)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static QosMessagePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1QosMessage.html</anchorfile>
      <anchor>a49c77c3642e2d9a738d38b109633e2ba</anchor>
      <arglist>(const ObjectPtr &amp;source, bool live, quint64 runningTime, quint64 streamTime, quint64 timestamp, quint64 duration)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::MiniObject</name>
    <filename>classQGst_1_1MiniObject.html</filename>
    <base>QGlib::RefCountedObject</base>
    <member kind="function">
      <type>MiniObjectPtr</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1MiniObject.html</anchorfile>
      <anchor>a6a75bbbdbd9179db0d81b2de7bd9fc04</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isWritable</name>
      <anchorfile>classQGst_1_1MiniObject.html</anchorfile>
      <anchor>ad6a5232527ef796f38616bb7089e7939</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>MiniObjectPtr</type>
      <name>makeWritable</name>
      <anchorfile>classQGst_1_1MiniObject.html</anchorfile>
      <anchor>ae04fd109d6bca609df8161a29ae773dd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGst_1_1MiniObject.html</anchorfile>
      <anchor>a365ea3b21913e3917b7f34b43b2d3530</anchor>
      <arglist>(bool increaseRef)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGst_1_1MiniObject.html</anchorfile>
      <anchor>a3e3ed5efd1fb75a9c756b8461da9f481</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Object</name>
    <filename>classQGst_1_1Object.html</filename>
    <base>QGlib::Object</base>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a1ee3f19ce963c7a3fbbb13f8b0c6a0de</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setName</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a7001e017cf480278915011ba8c85d1b6</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>ObjectPtr</type>
      <name>parent</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a1c2f28324d12389e27a3513e2d4e4ec0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setParent</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>acfc40c54f37b89e832392fd1541eb5b2</anchor>
      <arglist>(const ObjectPtr &amp;parent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unparent</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a5663403116d0070addc39496752a92b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAncestorOf</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a0641dc974e76c6be9d69056a87445ce6</anchor>
      <arglist>(const ObjectPtr &amp;object) const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>pathString</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>aac16029470afca4c33a0e6ca263a2cc8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>ref</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>a0ad797003a98bfd2d87229b4c8be1698</anchor>
      <arglist>(bool increaseRef)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>unref</name>
      <anchorfile>classQGst_1_1Object.html</anchorfile>
      <anchor>abe6912cbedaad7bc478adac6b7d5ad45</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Pad</name>
    <filename>classQGst_1_1Pad.html</filename>
    <base>QGst::Object</base>
    <member kind="function">
      <type>PadDirection</type>
      <name>direction</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a7fd18cf0b71391eb71de424d4a23154e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>parentElement</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a792139f684c6333c3ef9385678798a4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>PadPtr</type>
      <name>peer</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a466388892157a6ae6a7e59e526502c0d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLinked</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>ae79ae5b6860c5159ed07b891eeddc319</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>canLink</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>ad1f6da2e8790ea02ddf6c5b2e6a24258</anchor>
      <arglist>(const PadPtr &amp;sink) const </arglist>
    </member>
    <member kind="function">
      <type>PadLinkReturn</type>
      <name>link</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a9e83a0616ede85262813e63b6ce7d249</anchor>
      <arglist>(const PadPtr &amp;sink)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unlink</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>ac05c323b4a7fc3caa2f272f7614ee4b4</anchor>
      <arglist>(const PadPtr &amp;sink)</arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>caps</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a68e10654fe6b78d97b864df8ddf9093f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>allowedCaps</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>ae15edc9a497e9fb796e92bd12e74ea87</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>negotiatedCaps</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>ae270afe09c2e9b5e44af58d4605783a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setCaps</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>aad3c5219507bec726711c8a744e16b1d</anchor>
      <arglist>(const CapsPtr &amp;caps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a8d625dd0ca91729d66ab48dd33bdeb37</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setActive</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a81efa65c9866d945e3284a9651efd09c</anchor>
      <arglist>(bool active)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isBlocked</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a407666218eb80069f0379acb1f73a829</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isBlocking</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a1cb0d0017a4cac23194ccc92773d08e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setBlocked</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>aa0b89df65f07efec09cb80f0a41ae3c1</anchor>
      <arglist>(bool blocked)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>query</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a83e3027938bb46d2799638e9b2689091</anchor>
      <arglist>(const QueryPtr &amp;query)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sendEvent</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a91bf6a389e2ca834040ffd38bde01fb5</anchor>
      <arglist>(const EventPtr &amp;event)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static PadPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1Pad.html</anchorfile>
      <anchor>a2d25a46b5af6a9d55981a07cd4b5930e</anchor>
      <arglist>(PadDirection direction, const char *name=NULL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Pipeline</name>
    <filename>classQGst_1_1Pipeline.html</filename>
    <base>QGst::Bin</base>
    <member kind="function">
      <type>BusPtr</type>
      <name>bus</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a57f5a7a60fb7ec1dc555840aea86745a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockPtr</type>
      <name>clock</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a10f5584ca5f688782d74c7aa24aa9a08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setClock</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a5b40fe63e16fa94d32194eefd05f1315</anchor>
      <arglist>(const ClockPtr &amp;clock)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>useClock</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a8a463e3b4ecfc8c08a4cafd613848c1d</anchor>
      <arglist>(const ClockPtr &amp;clock)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enableAutoClock</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a31d98cc40f52b835cf73f090def9e66f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static PipelinePtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1Pipeline.html</anchorfile>
      <anchor>a84a7ac25ef8186fadceda65954ad6611</anchor>
      <arglist>(const char *name=NULL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::PluginFeature</name>
    <filename>classQGst_1_1PluginFeature.html</filename>
    <base>QGst::Object</base>
    <member kind="function">
      <type>uint</type>
      <name>rank</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>a4d1d32ed111d9151d78dc41fedadc626</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRank</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>ae99dd17a563586e638f5d73a9a7f94f5</anchor>
      <arglist>(uint rank)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>aaea9483cee04fe547ebe6d6caadd8c9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>a9f5c9b7c17b832974b14fd979c9cf858</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isAtLeastVersion</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>a53df34d7de664c9cc03161e791221e80</anchor>
      <arglist>(uint major, uint minor, uint micro) const </arglist>
    </member>
    <member kind="function">
      <type>PluginFeaturePtr</type>
      <name>load</name>
      <anchorfile>classQGst_1_1PluginFeature.html</anchorfile>
      <anchor>a1dc7d980b8b54acf71d1e80a69228b4b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>QGst::PropertyProbe</name>
    <filename>classQGst_1_1PropertyProbe.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>QList&lt; QGlib::ParamSpecPtr &gt;</type>
      <name>properties</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a579142ec7ca9b477df052047b791a3e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>propertySupportsProbe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a7f19eb0e08e2825401167e27a6a2f027</anchor>
      <arglist>(const QGlib::ParamSpecPtr &amp;property) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>propertySupportsProbe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>aa257a18260bc71170a423e416b944f55</anchor>
      <arglist>(const char *property) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>needsProbe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a641163ca849d80947365b38788006bc3</anchor>
      <arglist>(const QGlib::ParamSpecPtr &amp;property) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>needsProbe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a1b3885b57f5f64a8181726dade0166a1</anchor>
      <arglist>(const char *property) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a2b9926417bcc1655e4778cc83f17dc33</anchor>
      <arglist>(const QGlib::ParamSpecPtr &amp;property)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>afaa07bd47c764ff6cf0ea5d55842c0af</anchor>
      <arglist>(const char *property)</arglist>
    </member>
    <member kind="function">
      <type>QList&lt; QGlib::Value &gt;</type>
      <name>values</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a85336cd4ff3272df70e299a20e471b3c</anchor>
      <arglist>(const QGlib::ParamSpecPtr &amp;property) const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; QGlib::Value &gt;</type>
      <name>values</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a57490f544c2b14d40fe5dfc0f63cbcff</anchor>
      <arglist>(const char *property) const </arglist>
    </member>
    <member kind="function">
      <type>QList&lt; QGlib::Value &gt;</type>
      <name>probeAndGetValues</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a418a3aed822883776f6122013b1725c5</anchor>
      <arglist>(const QGlib::ParamSpecPtr &amp;property)</arglist>
    </member>
    <member kind="function">
      <type>QList&lt; QGlib::Value &gt;</type>
      <name>probeAndGetValues</name>
      <anchorfile>classQGst_1_1PropertyProbe.html</anchorfile>
      <anchor>a3cc9cad1f4414612541acdd92b49b7bb</anchor>
      <arglist>(const char *property)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Query</name>
    <filename>classQGst_1_1Query.html</filename>
    <base>QGst::MiniObject</base>
    <member kind="function">
      <type>QString</type>
      <name>typeName</name>
      <anchorfile>classQGst_1_1Query.html</anchorfile>
      <anchor>acc870df8f0b2183b9a9827718a0d03c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QueryType</type>
      <name>type</name>
      <anchorfile>classQGst_1_1Query.html</anchorfile>
      <anchor>a33d10865605b865386db983107f9be14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>StructurePtr</type>
      <name>internalStructure</name>
      <anchorfile>classQGst_1_1Query.html</anchorfile>
      <anchor>a8676963bae939e45be8fd284865119ac</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::PositionQuery</name>
    <filename>classQGst_1_1PositionQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1PositionQuery.html</anchorfile>
      <anchor>a5188078a159ba68fe80466eadb79545d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>position</name>
      <anchorfile>classQGst_1_1PositionQuery.html</anchorfile>
      <anchor>a7f86d71694b2ed38399b95e00a8e2bef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1PositionQuery.html</anchorfile>
      <anchor>a62621a6c72f4e556e2f056499604ee76</anchor>
      <arglist>(Format format, qint64 position)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static PositionQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1PositionQuery.html</anchorfile>
      <anchor>aa45dba7f811467060bf61d7ff668861b</anchor>
      <arglist>(Format format)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::DurationQuery</name>
    <filename>classQGst_1_1DurationQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1DurationQuery.html</anchorfile>
      <anchor>ab0607bbcf379e31642acbed29479fe86</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1DurationQuery.html</anchorfile>
      <anchor>a13d7c8ae85b72daa6b8bb41f008ed951</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1DurationQuery.html</anchorfile>
      <anchor>af9887f2282e157d9baeb3e15da50440c</anchor>
      <arglist>(Format format, qint64 duration)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static DurationQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1DurationQuery.html</anchorfile>
      <anchor>acc48716fe414ba25ae90dae2089a96ea</anchor>
      <arglist>(Format format)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::LatencyQuery</name>
    <filename>classQGst_1_1LatencyQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>bool</type>
      <name>hasLive</name>
      <anchorfile>classQGst_1_1LatencyQuery.html</anchorfile>
      <anchor>a569ff82228405d30ef5ed1a61fea2bbe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>minimumLatency</name>
      <anchorfile>classQGst_1_1LatencyQuery.html</anchorfile>
      <anchor>a45b564725ad1d3c1a0a7e710e29bbc6f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>maximumLatency</name>
      <anchorfile>classQGst_1_1LatencyQuery.html</anchorfile>
      <anchor>a5059ef9ac36df944204286a5323edd97</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1LatencyQuery.html</anchorfile>
      <anchor>add5ed0ae54561ab5882c8129343af046</anchor>
      <arglist>(bool live, ClockTime minimumLatency, ClockTime maximumLatency)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static LatencyQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1LatencyQuery.html</anchorfile>
      <anchor>a7ba09eddcd2d070e416321175dfa597b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SeekingQuery</name>
    <filename>classQGst_1_1SeekingQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>a1b15400bbf3502bd4b8cf32b19827423</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>seekable</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>af5dad3d0f1a218fe29646e4eda57d8f4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>segmentStart</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>a23dbb14b2673bb8f6f6f43748402e0bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>segmentEnd</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>a435628ce0b554b013bb0b88c3e29d2fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>a040481a8fd8ce9af24d40f152964940d</anchor>
      <arglist>(Format format, bool seekable, qint64 segmentStart, qint64 segmentEnd)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SeekingQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1SeekingQuery.html</anchorfile>
      <anchor>ae381cbb0b14ee6228047f0dc32a30bc5</anchor>
      <arglist>(Format format)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SegmentQuery</name>
    <filename>classQGst_1_1SegmentQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>a837d927e8cde1766d9d5ad70ae9be52b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rate</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>a69af3f451b0681b4d41618435f737738</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>startValue</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>adaa62a6f3e40040f73f48f1502f673da</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>stopValue</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>a1bf8d175c3d651247b7155e250d40ac9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>a93a7f4001b0a12393296f3387c501619</anchor>
      <arglist>(Format format, double rate, qint64 startValue, qint64 stopValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SegmentQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1SegmentQuery.html</anchorfile>
      <anchor>a7deb8d4d9b4b2dfdb9a08991211b04a6</anchor>
      <arglist>(Format format)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::ConvertQuery</name>
    <filename>classQGst_1_1ConvertQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>Format</type>
      <name>sourceFormat</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>af82b0eb05880053bb87cff25dcde200e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>sourceValue</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>a7adec36888b8e8bfef6d199a325d8347</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>destinationFormat</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>a84898446e99aea0ad54f1f33772b0ffe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>destinationValue</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>a04c1d96a1a76e833b65f29ee854bd4bb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>aea9ed9219c18facf99717da9dd404060</anchor>
      <arglist>(Format sourceFormat, qint64 sourcevalue, Format destinationFormat, qint64 destinationValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ConvertQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1ConvertQuery.html</anchorfile>
      <anchor>a8064e6597ace64d0b5f70686a5d12b49</anchor>
      <arglist>(Format sourceFormat, qint64 value, Format destinationFormat)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::FormatsQuery</name>
    <filename>classQGst_1_1FormatsQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>QList&lt; Format &gt;</type>
      <name>formats</name>
      <anchorfile>classQGst_1_1FormatsQuery.html</anchorfile>
      <anchor>a239b25247bee9a39a3a27d9784de67bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFormats</name>
      <anchorfile>classQGst_1_1FormatsQuery.html</anchorfile>
      <anchor>a7d832478c93ca94b0a7861fde764b2af</anchor>
      <arglist>(const QList&lt; Format &gt; &amp;formats)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FormatsQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1FormatsQuery.html</anchorfile>
      <anchor>a28d1f34f5dcb9b17a7cc5725482fc6db</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::BufferingQuery</name>
    <filename>classQGst_1_1BufferingQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>bool</type>
      <name>isBusy</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>aba89fdc1cca21919359405bea3603f8f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>percent</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a6dcf2b731dc36586496a51917c29ba16</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBufferingPercent</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a8ed0e22a5c4b107c330a419aa7b29d62</anchor>
      <arglist>(bool busy, int percent)</arglist>
    </member>
    <member kind="function">
      <type>BufferingMode</type>
      <name>mode</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>ab8bbe332d4e5275dbafcb28566ddbb43</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>averageIn</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a203baee98a8cc4f5ffb6b581a6e9ab9e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>averageOut</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a6a51f72601f171a7a8a64528a9456698</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>bufferingLeft</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>ad64e9fbb62727bf33f3148ab0ec8a24d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBufferingStats</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a57e6302823ab6a511e68a6ba2aa22e2c</anchor>
      <arglist>(BufferingMode mode, int averageIn, int averageOut, qint64 bufferingLeft)</arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>rangeFormat</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a3bb53e6244b16c32a2f34eaa1e3369f3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>rangeStart</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a08897781afdd73bf8ad19a97d0ad3ef5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>rangeStop</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a96229cca45006864c3daef6ddced0d76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>estimatedTotal</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a48e39841d1668e4cae88f21ccdf67a4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBufferingRange</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a91c353e8fe7a9458c34abf9a947c4ebb</anchor>
      <arglist>(Format rangeFormat, qint64 rangeStart, qint64 rangeStop, qint64 estimatedTotal)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BufferingQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1BufferingQuery.html</anchorfile>
      <anchor>a8a61e2cdc2bd50509df1420c2a065731</anchor>
      <arglist>(Format format)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::UriQuery</name>
    <filename>classQGst_1_1UriQuery.html</filename>
    <base>QGst::Query</base>
    <member kind="function">
      <type>QUrl</type>
      <name>uri</name>
      <anchorfile>classQGst_1_1UriQuery.html</anchorfile>
      <anchor>a51a4c07721332af91591e193e2cc8e07</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUri</name>
      <anchorfile>classQGst_1_1UriQuery.html</anchorfile>
      <anchor>a000ba04bdc96bcc00782d287c7415e22</anchor>
      <arglist>(const QUrl &amp;uri)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static UriQueryPtr</type>
      <name>create</name>
      <anchorfile>classQGst_1_1UriQuery.html</anchorfile>
      <anchor>aff2b4caeb54e3ef4afa631f6e9d54912</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::StreamVolume</name>
    <filename>classQGst_1_1StreamVolume.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>double</type>
      <name>volume</name>
      <anchorfile>classQGst_1_1StreamVolume.html</anchorfile>
      <anchor>acfb11fc3ffbd71798db368917105e512</anchor>
      <arglist>(StreamVolumeFormat format=StreamVolumeFormatLinear) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVolume</name>
      <anchorfile>classQGst_1_1StreamVolume.html</anchorfile>
      <anchor>a4c67a0b2071b8bbbf71357fb115a74ed</anchor>
      <arglist>(double value, StreamVolumeFormat format=StreamVolumeFormatLinear)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isMuted</name>
      <anchorfile>classQGst_1_1StreamVolume.html</anchorfile>
      <anchor>a36d8e7d45c9db23a9c7d07e6b494d98f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMuted</name>
      <anchorfile>classQGst_1_1StreamVolume.html</anchorfile>
      <anchor>a8f366b124f88b67bc33d75fd6d1e9bd4</anchor>
      <arglist>(bool muted)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>convert</name>
      <anchorfile>classQGst_1_1StreamVolume.html</anchorfile>
      <anchor>abc63eefb04d0cb1b03a097d7c9544e9e</anchor>
      <arglist>(StreamVolumeFormat from, StreamVolumeFormat to, double value)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>QGst::Fourcc</name>
    <filename>structQGst_1_1Fourcc.html</filename>
    <member kind="function">
      <type></type>
      <name>Fourcc</name>
      <anchorfile>structQGst_1_1Fourcc.html</anchorfile>
      <anchor>a4bf26f585680308d0f09579d327b87b6</anchor>
      <arglist>(char first, char second, char third, char fourth)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Fourcc</name>
      <anchorfile>structQGst_1_1Fourcc.html</anchorfile>
      <anchor>abc61a76041efd8f0df1b18173ce6c25e</anchor>
      <arglist>(const char str[4])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Fourcc</name>
      <anchorfile>structQGst_1_1Fourcc.html</anchorfile>
      <anchor>a88ca7a60f1546e5afa8cec68bfa93a3c</anchor>
      <arglist>(quint32 fourcc)</arglist>
    </member>
    <member kind="variable">
      <type>union QGst::Fourcc::@0</type>
      <name>value</name>
      <anchorfile>structQGst_1_1Fourcc.html</anchorfile>
      <anchor>a451e108a5df9203f9da67fcdf6815d8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct QGst::Fourcc::@0::@1</type>
      <name>as_bytes</name>
      <anchorfile>unionQGst_1_1Fourcc_1_1@0.html</anchorfile>
      <anchor>ab259e9a7633f722902a3632af89f873c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>first</name>
      <anchorfile>structQGst_1_1Fourcc_1_1@0_1_1@1.html</anchorfile>
      <anchor>a18d49077a4f7c5425a3d7d104fc21152</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>second</name>
      <anchorfile>structQGst_1_1Fourcc_1_1@0_1_1@1.html</anchorfile>
      <anchor>af6434b6fd553b3fc95ffb3be4e9a92e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>third</name>
      <anchorfile>structQGst_1_1Fourcc_1_1@0_1_1@1.html</anchorfile>
      <anchor>a5cad100004f76ddbc8dd95846f049615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>fourth</name>
      <anchorfile>structQGst_1_1Fourcc_1_1@0_1_1@1.html</anchorfile>
      <anchor>a25287299a9d5d7c4a3ecd24099de147a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>quint32</type>
      <name>as_integer</name>
      <anchorfile>unionQGst_1_1Fourcc_1_1@0.html</anchorfile>
      <anchor>ae715487948fdb9eead675dca8ffd9715</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>QGst::Fraction</name>
    <filename>structQGst_1_1Fraction.html</filename>
    <member kind="function">
      <type></type>
      <name>Fraction</name>
      <anchorfile>structQGst_1_1Fraction.html</anchorfile>
      <anchor>a82ca73d5891f1d400d39b44b75273aa6</anchor>
      <arglist>(int numerator, int denominator)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>structQGst_1_1Fraction.html</anchorfile>
      <anchor>a1e0745b64eb44a10d6315faafa6b0f72</anchor>
      <arglist>(const Fraction &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>structQGst_1_1Fraction.html</anchorfile>
      <anchor>a2f1b97aba4dcec023eda120fb54d8d47</anchor>
      <arglist>(const Fraction &amp;other) const </arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numerator</name>
      <anchorfile>structQGst_1_1Fraction.html</anchorfile>
      <anchor>a7ea593a1cba3a4b6e7f6cb128e3bb1c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>denominator</name>
      <anchorfile>structQGst_1_1Fraction.html</anchorfile>
      <anchor>a516e041feb66c52e2631f8cb9fd507f0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Structure</name>
    <filename>classQGst_1_1Structure.html</filename>
    <member kind="function">
      <type></type>
      <name>Structure</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ada2202022bd55f2710cba03bf4c3fa60</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Structure</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a46a525580d0a550b5f80228a09d23c10</anchor>
      <arglist>(const GstStructure *structure)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Structure</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a5800edbfc6c82a1c70db0b4aba61eb39</anchor>
      <arglist>(const Structure &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Structure &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>acfdf87fbf84a9621439f0ec6abcf1af1</anchor>
      <arglist>(const Structure &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a39f9e7273c5cbf6c4a4aa016affa5b69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>name</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a1edd1dc8a67e3b3c28b4209f65cd8485</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a1528472aa5ba15fb5e1cd7ec03f9e9e3</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::Value</type>
      <name>value</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a686ca3155899308032cdc5da368d552c</anchor>
      <arglist>(const char *fieldName) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ac1ea2183004bb03847884d6192cafa4b</anchor>
      <arglist>(const char *fieldName, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ac305e478f1d6acb88bea411f6d9dc5cd</anchor>
      <arglist>(const char *fieldName, const QGlib::Value &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>numberOfFields</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a08b8bad030416780a5e75d37576ba721</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>fieldName</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>acf297263ec1cf3e3dfe8bb7d950558c5</anchor>
      <arglist>(unsigned int fieldNumber) const </arglist>
    </member>
    <member kind="function">
      <type>QGlib::Type</type>
      <name>fieldType</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a5340942299da276833665b378a0e456a</anchor>
      <arglist>(const char *fieldName) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasField</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ae59e65bdcbf35deb3783ef579c6360d1</anchor>
      <arglist>(const char *fieldName) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasFieldTyped</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>aedf2a3ee203c813b882946200eb6d92d</anchor>
      <arglist>(const char *fieldName, QGlib::Type type) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeField</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a030669e6eb815da94b94a349132124b6</anchor>
      <arglist>(const char *fieldName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeAllFields</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>afed1d849fdc5988ab7d5fa95df1d099f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>toString</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a7201357afd30b14040ae4580ab84ad9c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator GstStructure *</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ae75da535d61e5ee7d4c49ea120e239e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const GstStructure *</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a42a55be235a9ad51c227d0e36d9e1ff5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Structure</type>
      <name>fromString</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a81344e8ae92517acb99c821e91be380a</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Structure</type>
      <name>fromString</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>a649f119fa0356b6090af318d05d5659e</anchor>
      <arglist>(const QString &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classQGst_1_1Structure.html</anchorfile>
      <anchor>ae029617cab3cca1e4ed0e02000fcb5e8</anchor>
      <arglist>(QDebug debug, const Structure &amp;structure)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::SharedStructure</name>
    <filename>classQGst_1_1SharedStructure.html</filename>
    <base>QGst::Structure</base>
    <member kind="function">
      <type>Structure</type>
      <name>copy</name>
      <anchorfile>classQGst_1_1SharedStructure.html</anchorfile>
      <anchor>adc8d4fef79e5b721b0e788ebc489eeff</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::TagList</name>
    <filename>classQGst_1_1TagList.html</filename>
    <member kind="function">
      <type></type>
      <name>TagList</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac10cc8662fb7d4ebd608dc17158a449b</anchor>
      <arglist>(const GstTagList *taglist)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TagList</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a0eba7688cf8aa85e2c388b5663848e4c</anchor>
      <arglist>(const TagList &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>TagList &amp;</type>
      <name>operator=</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac3616212b7f943bffec33510d8d23910</anchor>
      <arglist>(const TagList &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac0a4788746406c830923f7cd540b9bed</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>abb36969b7a30fa93db84ee985e4ebc82</anchor>
      <arglist>(const TagList &amp;other, TagMergeMode mode=TagMergeAppend)</arglist>
    </member>
    <member kind="function">
      <type>QGlib::Value</type>
      <name>tagValue</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a83e6250c9270330d01d978976cad83b1</anchor>
      <arglist>(const char *tag, int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTagValue</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7a8b302c4cf9214cd8513da0bac32978</anchor>
      <arglist>(const char *tag, const QGlib::Value &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>tagValueCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>abdf8494616dc7703c32b199562be3542</anchor>
      <arglist>(const char *tag) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5457858888957b534789fca2098b8903</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeTag</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aa1b60aea11bc59e4b254e532a1b6ab74</anchor>
      <arglist>(const char *tag)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator GstTagList *</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a6b0bda3f94e7d4e350a611abd8f1900e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const GstTagList *</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aa8e029e37277e78f9df81bfcb47482ef</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>title</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>adef0a8c6751089e16af1c198d08c2648</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitle</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a86d05de807135bd2c7c7ffd8e0ad4832</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>titleCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a957c892a043c6a61a08907bf8bd854f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>titleSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a659310827c6a6807c3666e76948b2e17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTitleSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a681dbd9e57be0fcba4f46448a1a29ad5</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>artist</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a38364f91116854914482acef642cb65e</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArtist</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a679ab61f42f33a7afe3a47f13098e912</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>artistCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab70230bf4bcd834dadf80c4298622b2a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>artistSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afbbd6574cb60eb1ab6514058dfc9085d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setArtistSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5d5c8ee956dc6a0ba7ec85c02eb4fb72</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>composer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a3c55deb1e7ea30220809b9ee70c203fd</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComposer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7982cc469016fca8c37ab0a8ad59f558</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>composerCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a15230724318f411df3cf576251eaf8aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QDate</type>
      <name>date</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9816307522e639ee7747abfd2b44de59</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a96830d99d0a20d5f70c7ba763f405999</anchor>
      <arglist>(const QDate &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>genre</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a00f0e03ae9ef7748871d00df0cd4d055</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGenre</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af7f5409fa916b74720cf87eab37f3dff</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>genreCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a90d5578a0a1d8f57a9f2975699cc8134</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>comment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>acbea77a86bdaefc7ad5f4fbadb20b30d</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac257fc800305eeaa1081999be40ae1d2</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>commentCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a43fecaaab55054540dc13baf1458a304</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>extendedComment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afb817996252fedc91b3b530156872ebb</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setExtendedComment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a03648ae74639c6f0098c1b4f79d10466</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>extendedCommentCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>acc8d5db95d98f8812673d19f3c85a339</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>trackNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ace53a31b5831e18acabdaf648cea08b5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrackNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a11a86b5fc981cd0e4385b5bf6fc7c801</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>trackCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a045c9e4c2e892972df44877e7bfd6df0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrackCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a356f0ef13216c55b4a13df591bcbda6b</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>albumVolumeNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae288f119d71a4ea043a96ac1b614d656</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlbumVolumeNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a93c541aff4218bc8cb816dcb785f7d95</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>albumVolumeCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a154047e88a8b12063fff38e0b6fff582</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlbumVolumeCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad674b8e778652d5fc7c05907f898fdc2</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>location</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a1d6216a5855d1b0bf946a402d2b1a957</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLocation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad341040496b93835ed453443c20f2f9d</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>locationCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af8684447751ad3c5afed0c95a4b1ab08</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>homepage</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae540fc70030f6d62fa1593197d66df46</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHomepage</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a1f62846c49eaed786c8f37684ea0d167</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>homepageCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9d073af2237b6cf561cbca9b66a7ba9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>description</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af3ea14b01da3b79f76d146e0c10cd90c</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDescription</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9ec27743b3cfd236e1f379cf6b427c71</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>descriptionCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad6fe44c4f6504d6269107cc3146ede28</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>version</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afee1970dd15253439984b6aab14e5a54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVersion</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a10eeb7385927744b84bfa94ac5cd8877</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>isrc</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a29bac2f22ccc99948716658835d283e7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIsrc</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>add618b4905265bad5952e25ad0ac210f</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>organization</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afc07cfe2994611813718d55839fd94a6</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setOrganization</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a857ef7f66a6da3ebe5018c7cb66a7625</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>organizationCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac59961ce5ce22324eea0bd8b62affc62</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>copyright</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ade8fff207944330805bb9f9a30dcc236</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCopyright</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9b0a865bf1ddd654e92fa53ec5dbec61</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>copyrightUri</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac9afd3c20c0b2bb6ad1bfcedbf1189a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCopyrightUri</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aabe1bc4f7c9a15caa645528a456f40a8</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>contact</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af1a4a84090e3ca88fb3b09e35e2359be</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setContact</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a6fcb22fd2ce57ca4d3ecee922c0b5167</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>contactCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a71fad51a9658cc0526508513abb4ed66</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>license</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a358d415dff326dbe1bf72461631b00e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLicense</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a6fc85850bdb0a582087a2620639f675b</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>licenseUri</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a26d76101cb5744fdaec6d51d30b1a805</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLicenseUri</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a667c5fa58d707c3f5a91f429f407ab5b</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>performer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5454bd8d89073803f7f154228ed1ed98</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPerformer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a6054ba811441db122dddaac3090a2766</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>performerCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a8e7d57838935460ef89d85ed5ec8955c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>duration</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5e9c44109d7bf6173b755d8f2cebc4b0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDuration</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a26dd0fe5425f8bc8cec732898ac54df0</anchor>
      <arglist>(quint64 value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>codec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac0afb099d5b3a1d371dba475bbd9ea18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a192634dc1a8606bb5c492203744c2447</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>videoCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a938d028e3de6128160c68188bc805f0f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVideoCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aeaef4d4cb43f262b8d3833c816186659</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>audioCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aa4e55fb33d82db968fcf855d27e96315</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAudioCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a776374322b30e7ed6a0be6205f72b771</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>subtitleCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac70ebb0eda6c8be15db363f0ca33f625</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSubtitleCodec</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9c3d2d77409927acd69f39394be92338</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>containerFormat</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a13274d69c39a773b7a93e236982b7e0e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setContainerFormat</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a78aaf0fe2c3afd954e60414bfe57da81</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>bitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a40188c4bb4c21221d8d00cb892aea83a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad99c110de36da63fc1892cd87757da21</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>nominalBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab93ff3e5a8d48b6fc51f1d81de807307</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNominalBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a33f6fd9f0e430837a09d7e0f7f28dbb2</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>minimumBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac775408ed690c0c4923d80a3c3adf18a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMinimumBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afd6116fa1f4890026506b46f5e916533</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>maximumBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a57de72c66251a6c759f70d44a79a4f8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaximumBitrate</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5f57365d66873fafd7115b1d12f9b6fd</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>serial</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac91168ad2931bbf7add7ae5cc64a1945</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSerial</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5cd0bb8ad924436e7b8727dc4964f4f6</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>encoder</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a1a76df2700e7fa99c3f59041a22d471e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEncoder</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a044b4267dea64998d03284646572533d</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>encoderVersion</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7cc6cb0bb2da9e0aea1f9a8a28fc654f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEncoderVersion</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a27c9b24214efab5170e72a565842ba1c</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>trackGain</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>abf76c26a93d1ab18964a7b0f69f7f33b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrackGain</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab5853aeb3c98ce4a0f8773a442a21b0a</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>trackPeak</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac01b0f1750ed0b5c79460315b6919d68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrackPeak</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a77421f0be7523ea82a2976240d39f39f</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>albumGain</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab5ce610bf10224e881d5254731205d7d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlbumGain</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae86f1c65da5cea1feec6e7d7e864d165</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>albumPeak</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a2d74c7235ed90d708a4be0d9c37cac80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAlbumPeak</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aafff6865f811be678b68bb3084833c52</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>referenceLevel</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9a33e6f32bf0abd149b2a297355314f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setReferenceLevel</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af879dcebede030875e82ebb41ff77798</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>languageCode</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a52ce35890881130c9d57e6be9e10019f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLanguageCode</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a566acf6784666b87ff6ec33b2856c0a8</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>image</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af7726a2e41aa086eb531408c3f0304f9</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setImage</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>abd541a651cb3374156008cf5f3ac8d06</anchor>
      <arglist>(const BufferPtr &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>imageCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad92f1bf4c3a3b3912557aa6b5c695f72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>previewImage</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a0262489a7f47ebe2e54fc1aaf7c3ed13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPreviewImage</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a48dd2ed88385ab17a573d814cf1ec1db</anchor>
      <arglist>(const BufferPtr &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>attachment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab4e3c969082d3251d67c08dc0408c58c</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setAttachment</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9aebbb2bdfe51d0dfb26f679e3b8f05b</anchor>
      <arglist>(const BufferPtr &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>attachmentCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9e75f390308604bf28c37367171a95d9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>beatsPerMinute</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a9df60967668a67bcfcd4135ed0db317e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBeatsPerMinute</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5a82508a781ebb1d371b282ea3b0e63a</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>keywords</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae9a595260f3ef788faee790096214027</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setKeywords</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a1df23c620da1014651be6431ef9765b9</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>keywordsCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a972abfd756db8f32dd82f548676b19f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>geoLocationName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac8d4d3dfe986a4bf18640f96d0577eb3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>seGeoLocationName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a159142d7a587a80b26506947f2f4b6d7</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationLatitude</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a2a98e3cd4bb9d98a6a17630a0b246051</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationLatitude</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a4f4bda14e7b63700b9f79de0bed5e463</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationLongitude</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a6357bdb96f396f53668d9c67e459789d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationLongitude</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>adadc4ba2caaee76355a14cbb9a615fca</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationElevation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a2f1fdddc403a94eccba1f1aaf77c1835</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationElevation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a00460e02ff3809559a4577370c93d716</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>geoLocationCountry</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad057f851c2e9f0c5a4a7e34cd7602f02</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationCountry</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a8c7e8ce34950b8714e941dba8e342e17</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>geoLocationCity</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a54a17de782d52f06bd3791d78c1b9713</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationCity</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae71f5208a9f1402abcec59a510c7f6d2</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>geoLocationSublocation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a0c991bd1a5a32cbdd29ade0f4a6f8cff</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationSublocation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7ab78220357cb6c31991f16d1fa65048</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationMovementSpeed</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a4aad2c97e6b0e35064ed7dc6d2a456fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationMovementSpeed</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a349ca1cea4e10c02df6a748d40cf2d99</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationMovementDirection</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab8b28d19850f936599c9097b7e6390b9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationMovementDirection</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a682be7292b98b3638fa41b396755ba32</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationCaptureDirection</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a0ca66ab68729a173635bda6b5c621e77</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationCaptureDirector</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a35265a45fc6d169ce0534a3ed4be3057</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>showName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aa8e839c6fdb23824ef6566e3c30d9872</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setShowName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af47e581f2b19408732477057c9c49ec1</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>showNameCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a02694aa279bf9ef33d25f0c267fac07e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>showSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ae344d0df15dfb2380ae9a544395f1af5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setShowSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>afb2b9e6f8aefabe541bfda52c59f5afa</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>showEpisodeNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac68f7e0e851feb40a56bed1bf7e60f50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setShowEpisodeNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7787b77291440f859482b6f4d9b9c642</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>showSeasonNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ac1a58f7d24f7cb4e46165b4ff9855377</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setShowSeasonNumber</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad5d5dc4b2b3eab0e423fbc329dc63d59</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>lyrics</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad189ab57a2abbade03c241b271ef2b5f</anchor>
      <arglist>(int index=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLyrics</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a3eb40bc76bf9d05c0f29e00a7ad24046</anchor>
      <arglist>(const QString &amp;value, TagMergeMode mode=TagMergeReplaceAll)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>lyricsCount</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aee7fb4a3edc424f2ec5d07c672e28ccf</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>composerSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a8fa7e8c4475d0264c03e1ed719e5a888</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComposerSortName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a7a41d271921b0e052766bc6e2c864929</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>grouping</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5090b6347aff3f9b451dfbd0e908a7a0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGrouping</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>acddce815abecf263c55127deece8a994</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>quint32</type>
      <name>userRating</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>abb4d5b3be9275da2ea9c992d38dff108</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUserRating</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>af80c0be20e70ae3960e2703c95f61e83</anchor>
      <arglist>(quint32 value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>deviceManufacturer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a710963743584ae494cf8dd2b9349ca09</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDeviceManufacturer</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ab6d9cfce1eb8e78771245b9b0927bfcf</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>deviceModel</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a22eb85c85e63a2e029ad3f2969cce03b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDeviceModel</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a39133e60a6246bf572fdf447e2b6215c</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>imageOrientation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a16d0d1f98a95fcf29d90d05bba1cba50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setImageOrientation</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a5cd79a4f29d43706a3d9071a7ce88245</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>applicationName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aec2af7bb55d87fd04ba1d1a112d51c23</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setApplicationName</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a0b4d3efcdd2418a1490a38cee44a2996</anchor>
      <arglist>(const QString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>applicationData</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>ad3a798567dcbd5b4d3db7bb84442766c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setApplicationData</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>acc64d57276d0bce2c8515d012b6bde30</anchor>
      <arglist>(const BufferPtr &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>QDateTime</type>
      <name>dateTime</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a302e0a4da0b6056afdb9530ee7717ac1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDateTime</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a8e7f3fc2137c087c256595dc11c2eaa8</anchor>
      <arglist>(const QDateTime &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>geoLocationHorizontalError</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a8f694cc1b088e59b52747d6124cad7e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setGeoLocationHorizontalError</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a946d2b066aff82ee8773a9d4f2713410</anchor>
      <arglist>(double value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static TagList</type>
      <name>merge</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>aa412e987d8cf3b4388e06868235fe168</anchor>
      <arglist>(const TagList &amp;firstList, const TagList &amp;secondList, TagMergeMode mode=TagMergeAppend)</arglist>
    </member>
    <member kind="function">
      <type>QDebug</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classQGst_1_1TagList.html</anchorfile>
      <anchor>a36c61fec0ec513fcd30e0cad9a530d31</anchor>
      <arglist>(QDebug debug, const TagList &amp;taglist)</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>QGst::UriHandler</name>
    <filename>classQGst_1_1UriHandler.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>UriType</type>
      <name>uriType</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>a0e521c4c55b2718b341e4f28bcb2bfe3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QStringList</type>
      <name>supportedProtocols</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>a43d13f8b00f671ba3f94e2d396264d67</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QUrl</type>
      <name>uri</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>a9b0d2e0e1f7126c1d10aed84984287a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setUri</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>af31ef4e86837624d8065cc4f14869d08</anchor>
      <arglist>(const QUrl &amp;uri)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>protocolIsSupported</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>acfd3af769e5d8978556042fdc54941a1</anchor>
      <arglist>(UriType type, const char *protocol)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ElementPtr</type>
      <name>makeFromUri</name>
      <anchorfile>classQGst_1_1UriHandler.html</anchorfile>
      <anchor>ae9f613d7eed016e359c2cf0b44bfb2a6</anchor>
      <arglist>(UriType type, const QUrl &amp;uri, const char *elementName=NULL)</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>QGst::VideoOrientation</name>
    <filename>classQGst_1_1VideoOrientation.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>bool</type>
      <name>horizontalFlipEnabled</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a6d4b80abb2746f1308a489a8202aba52</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>verticalFlipEnabled</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a3fc8c38e8305c3e34fcbcbfa96cbf428</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>horizontalCenter</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a16fc345017e0e878d85906eb80cc43c6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>verticalCenter</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>af6edbce2eea51d5554a21e9a66fb8668</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>enableHorizontalFlip</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a2e0c578995f1adb96eeab3a79c571fc8</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>enableVerticalFlip</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a169e3bfa53a0530502a05f9c3b589c99</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setHorizontalCenter</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>ab3342f12b67bbef7f94692544fac35a6</anchor>
      <arglist>(int center)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setVerticalCenter</name>
      <anchorfile>classQGst_1_1VideoOrientation.html</anchorfile>
      <anchor>a5995b714d445702e716c7a6cea1a3b00</anchor>
      <arglist>(int center)</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>QGst::XOverlay</name>
    <filename>classQGst_1_1XOverlay.html</filename>
    <base>QGlib::Interface</base>
    <member kind="function">
      <type>void</type>
      <name>expose</name>
      <anchorfile>classQGst_1_1XOverlay.html</anchorfile>
      <anchor>af7728031bcb4bfe60a1b72a6b3653c2e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWindowHandle</name>
      <anchorfile>classQGst_1_1XOverlay.html</anchorfile>
      <anchor>afe82040e95d9cdeaf475a7761dac92aa</anchor>
      <arglist>(WId id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enableEventHandling</name>
      <anchorfile>classQGst_1_1XOverlay.html</anchorfile>
      <anchor>a598718b68aca2cb3be638e8463a2f404</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setRenderRectangle</name>
      <anchorfile>classQGst_1_1XOverlay.html</anchorfile>
      <anchor>a3474cb261c7f09526d50c1fdc81498c4</anchor>
      <arglist>(int x, int y, int width, int height)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setRenderRectangle</name>
      <anchorfile>classQGst_1_1XOverlay.html</anchorfile>
      <anchor>a9501d0f24b97d600b3dfb6e3dea27164</anchor>
      <arglist>(const QRect &amp;rect)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>QGst::Parse</name>
    <filename>namespaceQGst_1_1Parse.html</filename>
    <member kind="function">
      <type>ElementPtr</type>
      <name>launch</name>
      <anchorfile>namespaceQGst_1_1Parse.html</anchorfile>
      <anchor>a516edea3114f528d3b10657a6a50bfd2</anchor>
      <arglist>(const char *description)</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>launch</name>
      <anchorfile>namespaceQGst_1_1Parse.html</anchorfile>
      <anchor>af557e8f62c0b657c39b5e528cf4fc18f</anchor>
      <arglist>(const char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>launch</name>
      <anchorfile>namespaceQGst_1_1Parse.html</anchorfile>
      <anchor>a7c3c2611c22b663bed269cae981061f2</anchor>
      <arglist>(const QString &amp;description)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>QGst::Private::Range</name>
    <filename>structQGst_1_1Private_1_1Range.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>Range</name>
      <anchorfile>structQGst_1_1Private_1_1Range.html</anchorfile>
      <anchor>a5a3ba142bd82ab4219aa5c303dc9794a</anchor>
      <arglist>(const T &amp;start, const T &amp;end)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>start</name>
      <anchorfile>structQGst_1_1Private_1_1Range.html</anchorfile>
      <anchor>a79907b9af4a927a2d5305df7aa417474</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>end</name>
      <anchorfile>structQGst_1_1Private_1_1Range.html</anchorfile>
      <anchor>a3620bac1e07e44a79cd9649c34aa1c5c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Quick::VideoItem</name>
    <filename>classQGst_1_1Quick_1_1VideoItem.html</filename>
    <member kind="function">
      <type></type>
      <name>VideoItem</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoItem.html</anchorfile>
      <anchor>a745f7b940ba90ce61df1c409b081be5a</anchor>
      <arglist>(QQuickItem *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>VideoSurface *</type>
      <name>surface</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoItem.html</anchorfile>
      <anchor>a30043fd2ea80f2a8037dae457f501d6d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSurface</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoItem.html</anchorfile>
      <anchor>a2f345eecdce5d15f5b1496dc24a0cf30</anchor>
      <arglist>(VideoSurface *surface)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual QSGNode *</type>
      <name>updatePaintNode</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoItem.html</anchorfile>
      <anchor>aaf2a1ed689dd8bb20b50a2ce2098b05a</anchor>
      <arglist>(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)</arglist>
    </member>
    <member kind="property">
      <type>QGst::Quick::VideoSurface</type>
      <name>surface</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoItem.html</anchorfile>
      <anchor>a8e30956dd6dbb51e4c717c1868a202b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Quick::VideoSurface</name>
    <filename>classQGst_1_1Quick_1_1VideoSurface.html</filename>
    <member kind="function">
      <type></type>
      <name>VideoSurface</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoSurface.html</anchorfile>
      <anchor>a25dd34f2f5d04eb1e86da8210bab234d</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>videoSink</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoSurface.html</anchorfile>
      <anchor>a851e1421403a7004f48fea50ec0aef9b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QTGSTREAMERQUICK_NO_EXPORT void</type>
      <name>onUpdate</name>
      <anchorfile>classQGst_1_1Quick_1_1VideoSurface.html</anchorfile>
      <anchor>aed5c2513adfa68f94a414672ba1f20ef</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>QGst::Ui</name>
    <filename>namespaceQGst_1_1Ui.html</filename>
    <class kind="class">QGst::Ui::GraphicsVideoSurface</class>
    <class kind="class">QGst::Ui::GraphicsVideoWidget</class>
    <class kind="class">QGst::Ui::VideoWidget</class>
  </compound>
  <compound kind="class">
    <name>QGst::Ui::GraphicsVideoSurface</name>
    <filename>classQGst_1_1Ui_1_1GraphicsVideoSurface.html</filename>
    <member kind="function">
      <type></type>
      <name>GraphicsVideoSurface</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoSurface.html</anchorfile>
      <anchor>ac64219adb5d82061fd9d59b253edc615</anchor>
      <arglist>(QGraphicsView *parent)</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>videoSink</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoSurface.html</anchorfile>
      <anchor>a3babe2d0b6e19808bb8c7137490eb692</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Ui::GraphicsVideoWidget</name>
    <filename>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</filename>
    <member kind="function">
      <type></type>
      <name>GraphicsVideoWidget</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</anchorfile>
      <anchor>a190a836369331878f64374957b4dc273</anchor>
      <arglist>(QGraphicsItem *parent=0, Qt::WindowFlags wFlags=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>paint</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</anchorfile>
      <anchor>aa76552c48546c98a4bc4a163d449a688</anchor>
      <arglist>(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0)</arglist>
    </member>
    <member kind="function">
      <type>GraphicsVideoSurface *</type>
      <name>surface</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</anchorfile>
      <anchor>ad63a875566cd059fa168f0e5c4942de1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSurface</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</anchorfile>
      <anchor>a38c69222a64748f7d6e3e1904ed8d4f2</anchor>
      <arglist>(GraphicsVideoSurface *surface)</arglist>
    </member>
    <member kind="property">
      <type>QGst::Ui::GraphicsVideoSurface</type>
      <name>surface</name>
      <anchorfile>classQGst_1_1Ui_1_1GraphicsVideoWidget.html</anchorfile>
      <anchor>aa24360eea50e9e39968b11a78cd7dda8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Ui::VideoWidget</name>
    <filename>classQGst_1_1Ui_1_1VideoWidget.html</filename>
    <member kind="function">
      <type></type>
      <name>VideoWidget</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>aea268e4cc486bc5db42d1d8ad934b9c4</anchor>
      <arglist>(QWidget *parent=0, Qt::WindowFlags f=0)</arglist>
    </member>
    <member kind="function">
      <type>ElementPtr</type>
      <name>videoSink</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>aa457310e2f224fd4ba7002759738413e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setVideoSink</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>af4fe386bb29a92c19596df1a0e442302</anchor>
      <arglist>(const ElementPtr &amp;sink)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>releaseVideoSink</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>a6991eedc169a8d0a6496c367f19a6924</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>watchPipeline</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>abe67def8a8e54ffe3e3705d978e5cfa2</anchor>
      <arglist>(const PipelinePtr &amp;pipeline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stopPipelineWatch</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>a7de3e106189decc6ab5b63be5710a148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>paintEvent</name>
      <anchorfile>classQGst_1_1Ui_1_1VideoWidget.html</anchorfile>
      <anchor>abfe37c43270a32e0aa0b52b1b47db31e</anchor>
      <arglist>(QPaintEvent *event)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>QGst::Utils</name>
    <filename>namespaceQGst_1_1Utils.html</filename>
    <class kind="class">QGst::Utils::ApplicationSink</class>
    <class kind="class">QGst::Utils::ApplicationSource</class>
  </compound>
  <compound kind="class">
    <name>QGst::Utils::ApplicationSink</name>
    <filename>classQGst_1_1Utils_1_1ApplicationSink.html</filename>
    <member kind="function">
      <type>ElementPtr</type>
      <name>element</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a518c6608396789ec8608d206a2cdace0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setElement</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a2097c739af167a3b08f1fa354ccd5f6f</anchor>
      <arglist>(const ElementPtr &amp;appsink)</arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>caps</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a108172e2ea92933c96e15d4dc3b63551</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCaps</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a29e1b1b295febbe916fc67fcc570b87e</anchor>
      <arglist>(const CapsPtr &amp;caps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEos</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a411fe841f976de36032e1d732367f664</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>maxBuffers</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>afc308d08d86dc5c5a9089c83665d5b92</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxBuffers</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>ad43a7b152d23b257b2a0575bac77de0f</anchor>
      <arglist>(uint maxbuffers)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dropEnabled</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>ad15299bb8fddc8ac307a1d734a1f8d23</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enableDrop</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a8bce8608aa1b859ed23c338314b43817</anchor>
      <arglist>(bool enable)</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>pullPreroll</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>ab5e9d353c4ac6862961e53609c7fd2c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BufferPtr</type>
      <name>pullBuffer</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>ac748f8e95c6100c3dcafa41c932ae5b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BufferListPtr</type>
      <name>pullBufferList</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a4db495c35d89f5ad6994e5dd96ecfbb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>eos</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a8b4b1f26bd6fbaad7ed336feecefb2e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual FlowReturn</type>
      <name>newPreroll</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a8ef1ce8cbe9d8261a524c503ee4b8ae9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual FlowReturn</type>
      <name>newBuffer</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a7995e62c8e1a5541148ca15495cc461d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual FlowReturn</type>
      <name>newBufferList</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSink.html</anchorfile>
      <anchor>a64c3f5a07b768135ed09023079925747</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QGst::Utils::ApplicationSource</name>
    <filename>classQGst_1_1Utils_1_1ApplicationSource.html</filename>
    <member kind="function">
      <type>ElementPtr</type>
      <name>element</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a178b60161548f3d062c5b92ce27f32bd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setElement</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>ae9b2de8e330c6a25654c2aed8768b1e6</anchor>
      <arglist>(const ElementPtr &amp;appsrc)</arglist>
    </member>
    <member kind="function">
      <type>CapsPtr</type>
      <name>caps</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>aeb4e1b6f9c0efc68cdf90b7f3ea3b341</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setCaps</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a6902c8b1b1f56af9e3af0ca7970900c5</anchor>
      <arglist>(const CapsPtr &amp;caps)</arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>minLatency</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a26132ee14746de5beb5298d3de7f8ded</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>maxLatency</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a9494cb372b49c63c53c026a7d6dbf398</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLatency</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a47ed2fab9dba60371c4dc69b0f2ba541</anchor>
      <arglist>(quint64 min, quint64 max)</arglist>
    </member>
    <member kind="function">
      <type>qint64</type>
      <name>size</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>ac7d8f3ca9a9a428883e485cb21ef86ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSize</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a147348b12909520e23e64045c5a2a40b</anchor>
      <arglist>(qint64 size)</arglist>
    </member>
    <member kind="function">
      <type>AppStreamType</type>
      <name>streamType</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a2e18191d2c2f3ac5f11e24d17e68d734</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStreamType</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a8f48fb3a7a1b57631eee1f6d1d33af06</anchor>
      <arglist>(AppStreamType type)</arglist>
    </member>
    <member kind="function">
      <type>quint64</type>
      <name>maxBytes</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a0e3be99d34b592fbbf41fa279d794a34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMaxBytes</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a0e12abec9a0cdeae0ab1d1a92270520a</anchor>
      <arglist>(quint64 max)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>blockEnabled</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a1a7068099451d010779d31cc3f79c9dc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>enableBlock</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>af031e3013e80a5eadf18ec5b27858aa5</anchor>
      <arglist>(bool enable)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLive</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>aa58b89198c1c10856b5aedc3af24dca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLive</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>af0ac4acb535add752684cdf8517afeb1</anchor>
      <arglist>(bool islive)</arglist>
    </member>
    <member kind="function">
      <type>uint</type>
      <name>minPercent</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a4e18576a8fbeed4f7dd6aa621e22bf6e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMinPercent</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a94fc2181fb3322941c1cd90776e12eec</anchor>
      <arglist>(uint min)</arglist>
    </member>
    <member kind="function">
      <type>Format</type>
      <name>format</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>abeb71efdd4ea5821587b8378b7d4c5f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFormat</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a65d5984b07504925eac3511371d9eafe</anchor>
      <arglist>(Format f)</arglist>
    </member>
    <member kind="function">
      <type>FlowReturn</type>
      <name>pushBuffer</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>aa76786dbd9ffde8f17716ce52df08c00</anchor>
      <arglist>(const BufferPtr &amp;buffer)</arglist>
    </member>
    <member kind="function">
      <type>FlowReturn</type>
      <name>endOfStream</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a42793262e513216e41a752466cb7d7d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>needData</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>acc2147eb24d0a2b533ba9e1a102ae582</anchor>
      <arglist>(uint length)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>enoughData</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>a85f8636bd3d7f18f5a0aeb1f658ab237</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>seekData</name>
      <anchorfile>classQGst_1_1Utils_1_1ApplicationSource.html</anchorfile>
      <anchor>ab9343f2229cc1dd5ff5813b2516e5227</anchor>
      <arglist>(quint64 offset)</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>QGlib/</name>
    <path>/home/simon/repos/qt-gstreamer/src/QGlib/</path>
    <filename>dir_147ce47606c0c4e93760d4f35b8a182c.html</filename>
    <file>connect.cpp</file>
    <file>connect.h</file>
    <file>connectimpl.h</file>
    <file>emitimpl.h</file>
    <file>error.cpp</file>
    <file>error.h</file>
    <file>gen.cpp</file>
    <file>global.h</file>
    <file>init.cpp</file>
    <file>init.h</file>
    <file>object.cpp</file>
    <file>object.h</file>
    <file>paramspec.cpp</file>
    <file>paramspec.h</file>
    <file>qglib_signal.h</file>
    <file>quark.cpp</file>
    <file>quark.h</file>
    <file>refpointer.h</file>
    <file>signal.cpp</file>
    <file>string_p.h</file>
    <file>type.cpp</file>
    <file>type.h</file>
    <file>value.cpp</file>
    <file>value.h</file>
    <file>wrap.cpp</file>
    <file>wrap.h</file>
  </compound>
  <compound kind="dir">
    <name>QGst/</name>
    <path>/home/simon/repos/qt-gstreamer/src/QGst/</path>
    <filename>dir_afbe94d90adb59192889e72937c34711.html</filename>
    <dir>QGst/Quick/</dir>
    <dir>QGst/Ui/</dir>
    <dir>QGst/Utils/</dir>
    <file>bin.cpp</file>
    <file>bin.h</file>
    <file>buffer.cpp</file>
    <file>buffer.h</file>
    <file>bufferlist.cpp</file>
    <file>bufferlist.h</file>
    <file>bus.cpp</file>
    <file>bus.h</file>
    <file>caps.cpp</file>
    <file>caps.h</file>
    <file>childproxy.cpp</file>
    <file>childproxy.h</file>
    <file>clock.cpp</file>
    <file>clock.h</file>
    <file>clocktime.cpp</file>
    <file>clocktime.h</file>
    <file>colorbalance.cpp</file>
    <file>colorbalance.h</file>
    <file>discoverer.cpp</file>
    <file>discoverer.h</file>
    <file>element.cpp</file>
    <file>element.h</file>
    <file>elementfactory.cpp</file>
    <file>elementfactory.h</file>
    <file>enums.h</file>
    <file>event.cpp</file>
    <file>event.h</file>
    <file>gen.cpp</file>
    <file>ghostpad.cpp</file>
    <file>ghostpad.h</file>
    <file>global.h</file>
    <file>init.cpp</file>
    <file>init.h</file>
    <file>message.cpp</file>
    <file>message.h</file>
    <file>miniobject.cpp</file>
    <file>miniobject.h</file>
    <file>object.cpp</file>
    <file>object.h</file>
    <file>objectstore.cpp</file>
    <file>objectstore_p.h</file>
    <file>pad.cpp</file>
    <file>pad.h</file>
    <file>parse.cpp</file>
    <file>parse.h</file>
    <file>pipeline.cpp</file>
    <file>pipeline.h</file>
    <file>pluginfeature.cpp</file>
    <file>pluginfeature.h</file>
    <file>propertyprobe.cpp</file>
    <file>propertyprobe.h</file>
    <file>query.cpp</file>
    <file>query.h</file>
    <file>streamvolume.cpp</file>
    <file>streamvolume.h</file>
    <file>structs.h</file>
    <file>structure.cpp</file>
    <file>structure.h</file>
    <file>taglist.cpp</file>
    <file>taglist.h</file>
    <file>urihandler.cpp</file>
    <file>urihandler.h</file>
    <file>value.cpp</file>
    <file>videoorientation.cpp</file>
    <file>videoorientation.h</file>
    <file>xoverlay.cpp</file>
    <file>xoverlay.h</file>
  </compound>
  <compound kind="dir">
    <name>qml/</name>
    <path>/home/simon/repos/qt-gstreamer/src/qml/</path>
    <filename>dir_20fee42767fb49db6854cb335485068a.html</filename>
    <dir>qml/quick1/</dir>
    <dir>qml/quick2/</dir>
  </compound>
  <compound kind="dir">
    <name>QGst/Quick/</name>
    <path>/home/simon/repos/qt-gstreamer/src/QGst/Quick/</path>
    <filename>dir_63c351f57c95f975b2dcbbdbe36f4bb1.html</filename>
    <file>global.h</file>
    <file>videoitem.cpp</file>
    <file>videoitem.h</file>
    <file>videosurface.cpp</file>
    <file>videosurface.h</file>
    <file>videosurface_p.h</file>
  </compound>
  <compound kind="dir">
    <name>qml/quick1/</name>
    <path>/home/simon/repos/qt-gstreamer/src/qml/quick1/</path>
    <filename>dir_c7a7c9e0102c0538b2acc56de4dda768.html</filename>
    <file>plugin.cpp</file>
    <file>videoitem.cpp</file>
    <file>videoitem.h</file>
  </compound>
  <compound kind="dir">
    <name>qml/quick2/</name>
    <path>/home/simon/repos/qt-gstreamer/src/qml/quick2/</path>
    <filename>dir_1c04f6be2310461aeeae029887af7671.html</filename>
    <file>plugin.cpp</file>
  </compound>
  <compound kind="dir">
    <name>QGst/Ui/</name>
    <path>/home/simon/repos/qt-gstreamer/src/QGst/Ui/</path>
    <filename>dir_38734a4d1fc0aa0b930eb34acf0abdfc.html</filename>
    <file>global.h</file>
    <file>graphicsvideosurface.cpp</file>
    <file>graphicsvideosurface.h</file>
    <file>graphicsvideosurface_p.h</file>
    <file>graphicsvideowidget.cpp</file>
    <file>graphicsvideowidget.h</file>
    <file>videowidget.cpp</file>
    <file>videowidget.h</file>
  </compound>
  <compound kind="dir">
    <name>QGst/Utils/</name>
    <path>/home/simon/repos/qt-gstreamer/src/QGst/Utils/</path>
    <filename>dir_fe1bb54ccf0430621c097d005fe9a586.html</filename>
    <file>applicationsink.cpp</file>
    <file>applicationsink.h</file>
    <file>applicationsource.cpp</file>
    <file>applicationsource.h</file>
    <file>global.h</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>QtGStreamer API Reference</title>
    <filename>index</filename>
    <docanchor file="index">using_qtgstreamer</docanchor>
    <docanchor file="index">api_reference</docanchor>
    <docanchor file="index">introduction</docanchor>
    <docanchor file="index">elements</docanchor>
  </compound>
</tagfile>
