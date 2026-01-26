## Strategy

1. **When to use**  
- When you have multiple interchangeable algorithms (sorting, pricing, routing, parking slot selection, etc.) and want to switch them at runtime via composition.[1][2]
- When conditional logic (`if/else` or `switch`) is exploding because of different behaviors that share the same input/output shape.[1]

2. **When not to use**  
- When the algorithm is simple and will never reasonably change; extracting to separate classes is just ceremony.[3]
- When the number of strategies is huge and non‑cohesive, leading to a class explosion that hurts readability.[3]

3. **Common interview mistakes**  
- Making strategies know too much about the context (violating single responsibility), instead of just implementing the algorithm interface.[4]
- Exposing concrete strategy types instead of coding everything against the `Strategy` interface, which kills the main benefit of decoupling.[1]

4. **Replacements / alternatives**  
- Simple function pointers, lambdas, or `std::function`/functional interfaces when you just need a pluggable behavior without a full class hierarchy.[5]
- Template parameter (in C++) when the strategy can be fixed at compile time and you want zero runtime overhead.[5]

5. **Special insight**  
- In LLD rounds, Strategy often pairs with Observer: observers maintain data, and different strategies use that data to make decisions (e.g., parking algorithms using parking‑lot state).[6][7]

***

## Factory Method

1. **When to use**  
- When a class needs to create objects but wants to delegate the exact concrete type to its subclasses via an overridable `createX()` method.[8][9]
- When you want to avoid calling `new` all over and centralize object creation based on some configuration or subtype.[9]

2. **When not to use**  
- When you only create one simple object and don’t expect new subtypes; a direct constructor call is fine.[9]
- When you actually need an entire *family* of related products; then Abstract Factory fits better.[8][9]

3. **Common interview mistakes**  
- Confusing Factory Method with a simple “utility factory class” (static `create()` methods) and not mentioning inheritance/overriding aspect.[8][9]
- Violating Open–Closed by stuffing big `if/else` logic inside a single factory instead of distributing creation via subclasses.[9]

4. **Replacements / alternatives**  
- Simple static factory functions when polymorphic extension is not needed.[9]
- Dependency injection containers or builders if construction logic becomes very complex.[10]

5. **Special insight**  
- Factory Method is often “hidden” in frameworks (e.g., framework calls your overridden creation hook), so mentioning framework extension points gains points.[9]

***

## Abstract Factory

1. **When to use**  
- When you must create *families* of related objects (e.g., `Button`, `Checkbox`, `Scrollbar`) that must match (Windows vs Mac theme).[8][9]
- When you want to switch whole product families at once via one factory interface.[9]

2. **When not to use**  
- When you only need one product type; Factory Method or a simple factory is enough.[8]
- When you expect to frequently add *new* product types; modifying the abstract factory interface breaks all factories.[10]

3. **Common interview mistakes**  
- Confusing Abstract Factory with Factory Method and not highlighting that Abstract Factory groups multiple creation methods.[8]
- Making factories leak concrete product types instead of returning only abstract product interfaces.[9]

4. **Replacements / alternatives**  
- Builder when the goal is to construct one complex object step‑by‑step rather than several related products.[10]
- Prototype when creating new instances mainly by cloning existing prototypes.[10]

5. **Special insight**  
- Abstract Factory trades off *extensibility in product families* (easy to add a new family) against *extensibility in product kinds* (hard to add a new kind). Mentioning this trade‑off is a strong design signal.[10][9]

***

## “Abstract Factory Method” (Factory Method vs Abstract Factory)

In many interviewers’ language, “abstract factory method” is just confusion between these two, so being crystal clear helps.

1. **When to use which**  
- Use Factory Method when you create one product type and rely on subclasses overriding a single creation method.[8]
- Use Abstract Factory when you need one object that can create multiple related products via several creation methods (`createButton()`, `createMenu()`, etc.).[8][9]

2. **When not to mix them up**  
- Don’t call a class with multiple `createX()` methods a Factory Method; that’s Abstract Factory.[8]
- Don’t implement a big static `create(type)` and call it Abstract Factory; that loses the family switching power.[9]

3. **Common interview mistakes**  
- Giving identical definitions for Factory Method and Abstract Factory; interviewers often test if you can differentiate.[8]
- Ignoring that Abstract Factory is about *families* and Factory Method is about *a single product’s creation hook*.[9]

4. **Replacements / combinations**  
- Often both patterns are combined: an Abstract Factory’s methods themselves are Factory Methods.[9]
- DI containers can replace many ad‑hoc abstract factories in modern codebases.[10]

5. **Special insight**  
- If you draw the class diagram in an LLD round and clearly show “one create vs multiple creates”, you stand out because most candidates stay hand‑wavy.[8][9]

***

## Singleton

1. **When to use**  
- When you truly need exactly one globally accessible instance: configuration, logging adapter, central cache, etc.[11]
- When creation is expensive and sharing one instance simplifies resource management.[12]

2. **When not to use**  
- When you can pass dependencies explicitly (DI) or use scoped lifetimes; global singletons make testing and evolution harder.[11]
- In highly concurrent systems where safe lazy initialization is non‑trivial and error‑prone.[12][11]

3. **Common interview mistakes**  
- Ignoring thread safety in lazy initialization (double‑checked locking done incorrectly, race conditions).[12][11]
- Hiding regular global mutable state inside Singleton and calling it “good design” without addressing testability.[11]

4. **Replacements / alternatives**  
- Dependency injection containers with a “singleton scope”, but still injected, not globally fetched.[11]
- Simple global object in small programs; or better, pass a shared instance explicitly where needed.[11]

5. **Special insight**  
- Many modern guides call Singleton an *anti‑pattern* in large systems, mainly because it introduces hidden coupling and makes testing brittle; acknowledging this nuance scores points.[12][11]

***

## Observer

1. **When to use**  
- When you have one‑to‑many dependency and want automatic notification when subject state changes (UI model–view, event systems, pub‑sub).[13]
- When you want loose coupling between the data source and multiple independent consumers.[7][13]

2. **When not to use**  
- When there is exactly one consumer and it is tightly coupled anyway; a direct callback or method call is simpler.[13]
- When ordering, transactional guarantees, or backpressure are critical; a more robust event bus or message queue can be safer.[14]

3. **Common interview mistakes**  
- Forgetting unsubscribe/observer removal, which easily leads to memory leaks and stale listeners.[13]
- Making observers pull data via getters instead of passing changed data in the notification, causing extra coupling.[7][13]

4. **Replacements / alternatives**  
- Event bus / message queue for cross‑process or distributed notifications.[14]
- Simple callback or promise/future when it is a one‑to‑one async response, not true one‑to‑many.[13]

5. **Special insight**  
- In LLD interviews (e.g., parking lot, order system), Observer often appears to keep multiple strategies or views in sync with one shared subject. Highlighting that pattern combo is powerful.[6][7]

***

## Decorator

1. **When to use**  
- When you want to add responsibilities to an object dynamically at runtime without exploding the inheritance tree.[15][16]
- When different combinations of behaviors are needed (compression + encryption + logging around I/O, etc.).[15]

2. **When not to use**  
- When the set of combinations is small and stable; inheritance or simple composition can be clearer.[15]
- When behavior order does not matter and you don’t actually need stacking/combining at runtime.[16]

3. **Common interview mistakes**  
- Implementing Decorator but then exposing the wrapped concrete type or breaking the interface, which defeats substitutability.[16][15]
- Confusing Decorator with inheritance; not explaining that Decorator is “has‑a (wraps)” while inheritance is “is‑a”.[15]

4. **Replacements / alternatives**  
- Simple composition: a class having a collaborator for extra behavior instead of fully wrapping the same interface.[15]
- Aspect‑oriented techniques or middleware chains in frameworks when cross‑cutting concerns (logging, auth) are needed.[16]

5. **Special insight**  
- A classic interview insight: Decorator lets you avoid \(O(n^k)\) subclasses for all combinations of k features across n base classes; you add one decorator per feature instead.[15]

***

## Command

1. **When to use**  
- When you want to encapsulate a request as an object so you can queue it, log it, or execute it later (job queues, task schedulers, GUI actions).[17][14]
- When you need undo/redo: each command knows how to `execute()` and `undo()`.[17][14]

2. **When not to use**  
- When a simple direct method call is enough and you don’t need history, queuing, or decoupling from the invoker.[14]
- When command objects would become too fine‑grained and flood the system, adding overhead without value.[14]

3. **Common interview mistakes**  
- Forgetting `undo()` semantics in designs where undo/redo is explicitly asked (editors, drawing apps).[17]
- Coupling invoker and receiver too tightly, instead of letting invoker operate only on command interfaces.[14]

4. **Replacements / alternatives**  
- Simple function callbacks or lambdas for lightweight commands when history/serialization are not required.[14]
- Event sourcing, where events (similar to commands) are persisted and used for rebuilding state, in more advanced designs.[14]

5. **Special insight**  
- Command often appears in game/IDE/editor interview questions, where commands are queued and can be replayed or undone; mentioning history/serialization is a strong differentiator.[17][14]

***
