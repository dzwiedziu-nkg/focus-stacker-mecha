import React, { useCallback, useState } from 'react';
import cn from 'classnames';
import axios from 'axios';
import { RewindIcon, StopIcon, PlayIcon } from './icons';

interface ToggleButtonProps {
  children: React.ReactNode;
  program: number;
  current: number;
  switchProgram: (p:number) => void;
  className: string;
}

function ProgramButton({
  children, program, current, switchProgram, className,
}: ToggleButtonProps) {
  const c = cn(
    'btn gap-2 border-4 hover:border-4',
    className,
    current === program ? 'border-black hover:border-black' : 'border-white hover:border-white',
  );

  return (
    <button className={c} onClick={() => switchProgram(program)}>
      {children}
    </button>
  );
}

interface SwitchProgramRequest {
  'program': number;
  'change_settings': number;
  'motor_time'?: number;
  'motor_pause'?: number;
  'focus_time'?: number;
  'exposure_time'?: number;
  'exposure_pause'?: number;
}

interface SwitchProgramResponse {
  'program': number;
  'message': string;
  'motor_time'?: number;
  'motor_pause'?: number;
  'focus_time'?: number;
  'exposure_time'?: number;
  'exposure_pause'?: number;
}

function useApi() {
  const [program, setProgram] = useState<number>(5);

  const switchProgram = useCallback((p: number) => {
    const request: SwitchProgramRequest = { program: p, change_settings: 0 };

    axios.post<SwitchProgramResponse>('/api/program', request).then((response) => {
      setProgram(response.data.program);
    });
  }, []);

  return { program, switchProgram };
}

function App() {
  const { program, switchProgram } = useApi();

  return (
    <div className="grid place-items-center" style={{ height: window.innerHeight }}>
      <div className="card card-compact bg-base-100 shadow-xl">
        { /* <figure><img src="https://api.lorem.space/image/shoes?w=400&h=225" alt="Shoes" /></figure> */ }
        <div className="card-body">
          <h2 className="font-bold text-center">Focus Stacker Mecha</h2>

          <div className="grid grid-cols-2 gap-4">
            <ProgramButton
              className="btn-error btn-lg col-span-2"
              current={program}
              program={0}
              switchProgram={switchProgram}
            >
              <StopIcon className="w-6 h-6" />
              <span>Stop</span>
            </ProgramButton>

            <ProgramButton
              className="btn-warning btn-lg"
              current={program}
              program={1}
              switchProgram={switchProgram}
            >
              <RewindIcon className="w-6 h-6" />
              <span>Rewind</span>
            </ProgramButton>
            <ProgramButton
              className="btn-warning btn-lg"
              current={program}
              program={2}
              switchProgram={switchProgram}
            >
              <span>Rewind</span>
              <RewindIcon className="w-6 h-6 rotate-180" />
            </ProgramButton>

            <ProgramButton
              className="btn-primary btn-lg"
              current={program}
              program={3}
              switchProgram={switchProgram}
            >
              <PlayIcon className="w-6 h-6 rotate-180" />
              <span>Photo</span>
            </ProgramButton>
            <ProgramButton
              className="btn-primary btn-lg"
              current={program}
              program={4}
              switchProgram={switchProgram}
            >
              <span>Photo</span>
              <PlayIcon className="w-6 h-6" />
            </ProgramButton>
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
