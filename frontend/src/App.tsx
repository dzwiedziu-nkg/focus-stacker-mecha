import React from 'react';

function App() {
  return (
    <div className="grid place-items-center" style={{ height: window.innerHeight }}>
      <div className="card card-compact bg-base-100 shadow-xl">
        { /* <figure><img src="https://api.lorem.space/image/shoes?w=400&h=225" alt="Shoes" /></figure> */ }
        <div className="card-body">
          <h2 className="font-bold text-center">Focus Stacker Mecha</h2>

          <div className="grid grid-cols-2 gap-4">
            <button className="btn btn-outline btn-error col-span-2">Stop</button>

            <button className="btn btn-outline btn-warning">Rewind</button>
            <button className="btn btn-outline btn-warning">Fast forward</button>

            <button className="btn btn-outline btn-primary">Photo, backward</button>
            <button className="btn btn-outline btn-primary">Photo, forward</button>
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
