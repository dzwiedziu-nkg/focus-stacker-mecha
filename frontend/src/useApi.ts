import { useCallback, useState } from 'react';
import axios from 'axios';

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

export default useApi;
