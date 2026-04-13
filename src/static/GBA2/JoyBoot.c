#include "GBA2/gba2.h"

#include "_mem.h"
#include "MSL_C/printf.h"

static Joy_wrk_c g_Joy_wrk;
int Port;

static u32 mJOYSIO_ConvData(u8* data) {
  u8 conv_buf[sizeof(u32)];
  
  conv_buf[0] = data[3];
  conv_buf[1] = data[2];
  conv_buf[2] = data[1];
  conv_buf[3] = data[0];

  return *(u32*)conv_buf;
}

extern void mGcgba_Init() { }

extern void mGcgba_InitVar() {
  memset(&g_Joy_wrk, 0, sizeof(Joy_wrk_c));
}

extern void mGcgba_EndComm() {
  Port = -1;
}

extern int mGcgba_ConnectEnabled() {
#ifdef TARGET_PC
  /* Pretend a GBA is connected so Kapp'n lets us travel to the island. */
  Port = GBA_CHAN0;
  return GBA2_GBA_STATE_SUCCESS;
#else
  int state = GBA2_GBA_STATE_TRANSMITTING;

  if (g_Joy_wrk.cmd_attempts < GBA2_CONNECTED_TRIES) {
    int port;

    for (port = 0; port < GBA_MAX_CHAN; port++) {
      u8 status;

      if (GBAGetStatus(port, &status) == GBA_READY) {
        state = GBA2_GBA_STATE_SUCCESS;
        Port = port;
        break;
      }
    }

    if (state != GBA2_GBA_STATE_SUCCESS) {
      Port = -1;
    }
  }
  else {
    state = GBA2_GBA_STATE_ERROR;
  }

  g_Joy_wrk.cmd_attempts++;
  return state;
#endif
}

static void CallBack(s32 port, s32 ret) {
  g_Joy_wrk.port_connection_states[port] = ret;
}

extern int mGcgba_Boot(u8* data_buf, size_t buf_size) {
  static u8 state;
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage) {
        case 0:
        {
          int port;
          for (port = 0; port < GBA_MAX_CHAN; port++) {
            g_Joy_wrk.port_connection_states[port] = GBA2_GBA_STATE_SUCCESS;
          }

          g_Joy_wrk.cmd_stage++;
          break;
        }

        case 1:
        {
          if (GBAGetProcessStatus(Port, NULL) == GBA_BUSY) {
            g_Joy_wrk.cmd_attempts = 0;
          }
          else if (g_Joy_wrk.port_connection_states[Port] == GBA_READY) {
            gba_state = GBA2_GBA_STATE_SUCCESS;
          }
          else {
            if (GBAJoyBootAsync(Port, 1, 2, data_buf, buf_size, &state, CallBack)) {
              g_Joy_wrk.port_connection_states[Port] = GBA2_GBA_STATE_TRANSMITTING;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

static int mJOYSIO_OpenConnection(Joy_wrk_c* joywork) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;
  u8 status;

  if (GBAGetStatus(Port, &status) != GBA_READY) {
    gba_state = GBA2_GBA_STATE_ERROR;
  }
  else {
    if (joywork->gba_awaiting_ack == TRUE) {
      u32 data = mJOYSIO_ConvData((u8*)"GAFJ");

      if (GBAWrite(Port, (u8*)&data, &status) == GBA_READY) {
        gba_state = GBA2_GBA_STATE_SUCCESS;
      }
      else {
        gba_state = GBA2_GBA_STATE_ERROR;
      }
    }
    else {
      if (status & GBA_JSTAT_SEND) {
        u32 recv;
        if (GBARead(Port, (u8*)&recv, &status) == GBA_READY) {
          if (*(u32*)"AAFJ" == recv) {
            joywork->gba_awaiting_ack = TRUE;
          }
        }
        else {
          gba_state = GBA2_GBA_STATE_ERROR;
        }
      }

      if (gba_state == GBA2_GBA_STATE_TRANSMITTING && joywork->gba_awaiting_ack == FALSE && GBAReset(Port, &status) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
      }
    }
  }

  return gba_state;
}

static int mGcgba_StartScan(Joy_wrk_c* joywork, u32 cmd) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;
  u8 status;
  u8 status2;
  u32 send;
  u32 recv;

  if (GBAGetStatus(Port, &status) == GBA_READY) {
    if (joywork->scan_state == 1) {
      if (status & GBA_JSTAT_SEND) {
        
        if (GBARead(Port, (u8*)&recv, &status2) != GBA_READY) {
          gba_state = GBA2_GBA_STATE_ERROR;
        }
        else {
          switch (mJOYSIO_ConvData((u8*)&recv)) {
            case 0xFFFE0208:
            {
              gba_state = GBA2_GBA_STATE_SUCCESS;
              break;
            }

            case 0xFFFE020A:
            {
              gba_state = GBA2_GBA_STATE_ALREADY_EXIST;
              break;
            }
            
            default:
            {
              gba_state = GBA2_GBA_STATE_ERROR;
              break;
            }
          }
        }
      }
      else {
        send = 0xFFFE0109;
        send = mJOYSIO_ConvData((u8*)&send);

        if (GBAWrite(Port, (u8*)&send, &status) != GBA_READY) {
          gba_state = GBA2_GBA_STATE_ERROR;
        }

        if (GBAReset(Port, &status2) != GBA_READY) {
          gba_state = GBA2_GBA_STATE_ERROR;
        }
      }
    }
    else if (status & GBA_JSTAT_SEND) {
      recv;
      if (GBARead(Port, (u8*)&recv, &status2) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
      }
      else{
        switch (mJOYSIO_ConvData((u8*)&recv)) {
          case 0xFFFE0208:
          {
            joywork->scan_state = 1;
            break;
          }

          case 0xFFFE020A:
          {
            gba_state = GBA2_GBA_STATE_ALREADY_EXIST;
            break;
          }

          default:
          {
            gba_state = GBA2_GBA_STATE_ERROR;
            break;
          }
        }
      }
    }
    else {
      send = cmd;
      send = mJOYSIO_ConvData((u8*)&send);

      if (GBAWrite(Port, (u8*)&send, &status) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
      }

      if (GBAReset(Port, &status2) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
      }
    }
  }

  return gba_state;
}

static int mGcgba_IsTypes(Joy_wrk_c* joywork, u32 load_type, u32 program_type) {
  int gba_status = GBA2_GBA_STATE_TRANSMITTING;
  u8 status;
  u32 send;

  if (GBAGetStatus(Port, &status) != GBA_READY) {
    gba_status = GBA2_GBA_STATE_ERROR;
  }
  else {
    if (status & GBA_JSTAT_SEND) {
        u32 recv;
        u8 readStatus;
        
        if (GBARead(Port, (u8*)&recv, &readStatus) != GBA_READY) {
          gba_status = GBA2_GBA_STATE_ERROR;
          goto exit;
        }
        else {
            if (joywork->scan_state == 1) {
              if (load_type == mJOYSIO_ConvData((u8*)&recv)) {
                gba_status = GBA2_GBA_STATE_SUCCESS;
                goto exit;
              }
        
              if (program_type == mJOYSIO_ConvData((u8*)&recv)) {
                gba_status = GBA2_GBA_STATE_ALREADY_EXIST;
                goto exit;
              }
        
              gba_status = GBA2_GBA_STATE_ERROR;
              goto exit;
            }
            
            joywork->cmd_attempts = 0;
        }
      }

    send = 0xFFFE0105;
    send = mJOYSIO_ConvData((u8*)&send);

    if (GBAWrite(Port, (u8*)&send, &status) == GBA_READY) {
      joywork->scan_state = 1;
    }
    else {
      gba_status = GBA2_GBA_STATE_ERROR;
    }
  }

  exit:
  return gba_status;
}

extern int mGcgba_IsEditor() {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage)
      {
        case 0:
        {
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int attempt;

          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_IsTypes(&g_Joy_wrk, 0xFFFE0206, 0xFFFE0207);

            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

extern int mGcgba_IsIsland() {
#ifdef TARGET_PC
  /* No GBA: fail fast so Sendo falls back to the RAM island data path. */
  return GBA2_GBA_STATE_ERROR;
#else
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage)
      {
        case 0:
        {
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int attempt;

          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_IsTypes(&g_Joy_wrk, 0xFFFE0207, 0xFFFE0206);

            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
#endif
}

static int mGcgba_Recv_sub(Joy_wrk_c* jwork, u8* recv_buf, size_t buf_size, u32 cmd) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;
  u8 status;
  u8 read_status;
  u32 gba_cmd;
  u32 recv;
  u32 data;

  if (GBAGetStatus(Port, &status) != GBA_READY) {
    gba_state = GBA2_GBA_STATE_ERROR;
  }
  else {
    if (status & GBA_JSTAT_SEND) {
      
      if (GBARead(Port, (u8*)&recv, &read_status) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
      }
      else {
        data = mJOYSIO_ConvData((u8*)&recv);
        switch (jwork->recv_state) {
          case 0:
          {
            if (data == 0xFFFE0204) {
              jwork->readwrite_ofs = 0;
              jwork->packets_processed = 0;
              jwork->packet_block_checksum = 0;
              jwork->total_xfer_checksum = 0;
              jwork->checksum_valid = FALSE;
              jwork->checksum_invalid = FALSE;
              jwork->recv_state++;
            }
            break;
          }

          case 1:
          {
            if (jwork->readwrite_ofs == (int)buf_size / 4) {
              jwork->total_xfer_checksum += data;
              if (jwork->total_xfer_checksum == 0xFFFFFFFF) {
                jwork->checksum_valid = TRUE;
              }
              else {
                jwork->checksum_invalid = TRUE;
              }

              jwork->recv_state++;
            }
            else if ((jwork->packets_processed & 0xFF) == 0xFF) {
              jwork->packet_block_checksum += data;

              if (jwork->packet_block_checksum != 0xFFFFFFFF) {
                gba_state = GBA2_GBA_STATE_ERROR;
              }

              jwork->packet_block_checksum = 0;
            }
            else {
              memcpy(recv_buf + jwork->readwrite_ofs * sizeof(u32), (u8*)&recv, sizeof(u32));
              jwork->packet_block_checksum += data;
              jwork->total_xfer_checksum += data;
              jwork->readwrite_ofs++;
            }

            jwork->packets_processed++;
            jwork->cmd_attempts = 0;
            break;
          }

          case 2:
          {
            if (data == 0xFFFE0208) {
              gba_state = GBA2_GBA_STATE_SUCCESS;
            }
            else if (data == 0xFFFE0209) {
              gba_state = GBA2_GBA_STATE_ERROR;
            }

            break;
          }
        }
      }
    }
  }

  if (gba_state == GBA2_GBA_STATE_TRANSMITTING) {
    if (jwork->checksum_valid == TRUE) {
      gba_cmd = 0xFFFE0106;
    }
    else {

      if (jwork->checksum_invalid == TRUE) {
        gba_cmd = 0xFFFE0107;
      }
      else {
        gba_cmd = cmd;
      }
    }

    gba_cmd = mJOYSIO_ConvData((u8*)&gba_cmd);
    if (GBAWrite(Port, (u8*)&gba_cmd, &read_status) != GBA_READY) {
      gba_state = GBA2_GBA_STATE_ERROR;
    }
  }

  return gba_state;
}

extern int mGcgba_Recv(u8* recv_bufp, size_t recv_buf_size) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage)
      {
        case 0:
        {
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int attempt;

          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_Recv_sub(&g_Joy_wrk, recv_bufp, recv_buf_size, 0xFFFE0102);

            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

extern int mGcgba_Read(u8* read_buf, size_t read_buf_size, u8 prog_type) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    printf("port 設定されていない\n"); // port not set
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if ((g_Joy_wrk.cmd_stage == 1 && g_Joy_wrk.cmd_attempts < GBA2_READ_TRIES) ||
        (g_Joy_wrk.cmd_stage != 1 && g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES)
    ) {
      switch (g_Joy_wrk.cmd_stage) {
        case 0:
        {
          printf("read:イニシャルコード交換\n"); // read: initial code exchange
          
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int res;
          printf("read:スキャン\n"); // read: scan
          
          switch (prog_type) {
            case GBA2_EAPPLI_TYPE_NEEDLEWORK:
            {
              res = mGcgba_StartScan(&g_Joy_wrk, 0xFFFE0108);
              break;
            }
            
            case GBA2_EAPPLI_TYPE_MUSICSCORE:
            {
              res = mGcgba_StartScan(&g_Joy_wrk, 0xFFFE010B);
              break;
            }

            default: /* GBA2_EAPPLI_TYPE_PTERMINAL */
            {
              res = mGcgba_StartScan(&g_Joy_wrk, 0xFFFE010C);
              break;
            }
          }

          if (res == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
            g_Joy_wrk.cmd_attempts = 0;
          }
          else if (res == GBA2_GBA_STATE_ERROR) {
            gba_state = GBA2_GBA_STATE_ERROR;
          }
          break;
        }

        case 2:
        {
          int attempt;
          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_Recv_sub(&g_Joy_wrk, read_buf, read_buf_size, 0xFFFE010A);
            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }

          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

extern int mGcgba_CheckRecv(u8* recv_bufp, size_t recv_buf_size) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage)
      {
        case 0:
        {
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int attempt;

          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_Recv_sub(&g_Joy_wrk, recv_bufp, recv_buf_size, 0xFFFE0101);

            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

static int mGcgba_Send_sub(Joy_wrk_c* jwork, u8* send_bufp, size_t send_buf_size) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;
  u8 status;
  u8 read_status;
  u8 received_data;
  u8 sent_data;
  int recv_cmd;
  u32 send_cmd;
  u32 recv;

  if (GBAGetStatus(Port, &status) != GBA_READY) {
    gba_state = GBA2_GBA_STATE_ERROR;
  }
  else {
    received_data = FALSE;
    sent_data = FALSE;
    jwork->status = status;

    if (status & GBA_JSTAT_SEND) {
      if (GBARead(Port, (u8*)&recv, &read_status) != GBA_READY) {
        gba_state = GBA2_GBA_STATE_ERROR;
        goto exit;
      }

      recv_cmd = mJOYSIO_ConvData((u8*)&recv);
      received_data = TRUE;
    }

    switch (jwork->send_state) {
      case 0:
      {
        if (received_data == TRUE && recv_cmd == 0xFFFE0104) {
          jwork->readwrite_ofs = 0;
          jwork->packets_processed = 0;
          jwork->packet_block_checksum = 0;
          jwork->total_xfer_checksum = 0;
          jwork->send_state++;
        }
        break;
      }

      case 1:
      {
        if ((status & GBA_JSTAT_RECV) == 0) {
          if (jwork->readwrite_ofs == (int)send_buf_size / 4) {
            send_cmd = ~jwork->total_xfer_checksum;
            jwork->send_state++;
          }
          else if ((jwork->packets_processed & 0xFF) == 0xFF) {
            send_cmd = ~jwork->packet_block_checksum;
            jwork->packet_block_checksum = 0;
          }
          else {
            send_cmd = *(u32*)(send_bufp + jwork->readwrite_ofs * sizeof(u32));
            jwork->packet_block_checksum += send_cmd;
            jwork->total_xfer_checksum += send_cmd;
            jwork->readwrite_ofs++;
          }

          if (GBAWrite(Port, (u8*)&send_cmd, &read_status) != GBA_READY) {
            gba_state = GBA2_GBA_STATE_ERROR;
          }

          sent_data = TRUE;
          jwork->packets_processed++;
          jwork->cmd_attempts = 0;
        }
        else {
          if (GBAReset(Port, &read_status) != GBA_READY) {
            gba_state = GBA2_GBA_STATE_ERROR;
          }
        }
        break;
      }

      case 2:
      {
        if (received_data == TRUE) {
          if (recv_cmd == 0xFFFE0208) {
            gba_state = GBA2_GBA_STATE_SUCCESS;
          }
          else if (recv_cmd == 0xFFFE0209) {
            gba_state = GBA2_GBA_STATE_ERROR;
          }
        }

        break;
      }
    }
  }

  exit:
  if (gba_state == GBA2_GBA_STATE_TRANSMITTING && jwork->send_state != 1 && sent_data == FALSE) {
    send_cmd = 0xFFFE0202;
    send_cmd = mJOYSIO_ConvData((u8*)&send_cmd);

    if (GBAWrite(Port, (u8*)&send_cmd, &read_status) != GBA_READY) {
      gba_state = GBA2_GBA_STATE_ERROR;
    }
  }

  return gba_state;
}

extern int mGcgba_Send(u8* send_bufp, size_t send_buf_size) {
  int gba_state = GBA2_GBA_STATE_TRANSMITTING;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    return GBA2_GBA_STATE_ERROR;
  }
  else {
    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      switch (g_Joy_wrk.cmd_stage)
      {
        case 0:
        {
          if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
            g_Joy_wrk.cmd_stage++;
          }
          break;
        }

        case 1:
        {
          int attempt;

          for (attempt = 0; attempt < 24; attempt++) {
            gba_state = mGcgba_Send_sub(&g_Joy_wrk, send_bufp, send_buf_size);

            if (gba_state != GBA2_GBA_STATE_TRANSMITTING) {
              break;
            }
          }
          break;
        }
      }
    }
    else {
      gba_state = GBA2_GBA_STATE_ERROR;
    }

    g_Joy_wrk.cmd_attempts++;
  }

  return gba_state;
}

static u32 changeEndian(u32 v) {
  return ((v >> 24) & 0xFF) |
         ((v >> 8) & 0xFF00) |
         ((v & 0xFF00) << 8) |
         ((v & 0xFF) << 24);
}

extern int mGcgba_send_eAppri(u8* eappli_p, size_t eappli_size) {
  int gba_state = GBA2_EAPPLI_TRANSMITTING;
  int gba_status;
  u32 data;
  u32 recv;
  u8 status;

  if (Port < GBA_CHAN0 || Port >= GBA_MAX_CHAN) {
    gba_state = GBA2_EAPPLI_FAILURE_NO_GBA;
  }
  else {
    g_Joy_wrk.cmd_attempts++;

    if (g_Joy_wrk.cmd_attempts < GBA2_DEFAULT_TRIES) {
      
      gba_status = GBAGetStatus(Port, &status);
      if (gba_status == GBA_READY) {
        if ((status & GBA_JSTAT_RECV) == 0) {
          g_Joy_wrk.recv_wait = 0;
        }
        else if (g_Joy_wrk.recv_wait < GBA2_SEND_RECV_TRIES) {
          g_Joy_wrk.recv_wait++;
        }
      }

      if (gba_status == GBA_READY && g_Joy_wrk.recv_wait <= GBA2_SEND_RECV_TRIES - 1) {
        switch (g_Joy_wrk.cmd_stage) {
          case SEND_EAPPLI_STATE_WAIT_FOR_GBA:
          {
            if ((status & GBA_JSTAT_SEND) != 0 &&
                (status & GBA_JSTAT_PSF1) != 0 &&
                (GBARead(Port, (u8*)&recv, &status) == GBA_READY) &&
                (*(u32*)"PSAE" == recv)
            ) {
              g_Joy_wrk.cmd_attempts = 0;
              g_Joy_wrk.cmd_stage++;
            }
            else {
              if (GBAReset(Port, &status) != GBA_READY) {
                gba_state = GBA2_EAPPLI_FAILURE_NO_GBA;
              }
            }
            break;
          }

          case SEND_EAPPLI_STATE_GC_ACKNOWLEDGE_TO_GBA:
          {
            data = *(u32*)"PSAE";
            if (GBAWrite(Port, (u8*)&data, &status) == GBA_READY) {
              g_Joy_wrk.cmd_attempts = 0;
              g_Joy_wrk.cmd_stage++;
              g_Joy_wrk.cmd_stage++; // lol duplication
            }
            break;
          }

          // case 2 unused

          case SEND_EAPPLI_STATE_GC_SEND_EAPPLI_SIZE_TO_GBA:
          {
            if ((status & GBA_JSTAT_PSF0) && (status & GBA_JSTAT_PSF1)) {
              data = changeEndian(eappli_size);
              if (GBAWrite(Port, (u8*)&data, &status) == GBA_READY) {
                g_Joy_wrk.cmd_attempts = 0;
                g_Joy_wrk.cmd_stage++;
              }
            }
            break;
          }

          case SEND_EAPPLI_STATE_WAIT_FOR_GBA_ACKNOWLEDGED_EAPPLI_SIZE:
          {
            if ((status & GBA_JSTAT_SEND) && GBARead(Port, (u8*)&recv, &status) == GBA_READY && eappli_size == changeEndian(recv)) {
              g_Joy_wrk.cmd_attempts = 0;
              g_Joy_wrk.readwrite_ofs = 0;
              g_Joy_wrk.cmd_stage++;
            }
            break;
          }

          case SEND_EAPPLI_STATE_GC_SEND_EAPPLI_DATA_TO_GBA:
          {
            if ((u32)g_Joy_wrk.readwrite_ofs >= eappli_size / sizeof(u32)) {
              g_Joy_wrk.cmd_stage++;
            }
            else {
              if ((status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_FLAGS_MASK) {
                return GBA2_EAPPLI_FAILURE_NO_GBA;
              }

              if ((status & GBA_JSTAT_RECV) == 0) {
                data = *(u32*)(eappli_p + g_Joy_wrk.readwrite_ofs * sizeof(u32));

                if (GBAWrite(Port, (u8*)&data, &status) == GBA_READY) {
                  g_Joy_wrk.cmd_attempts = 0;
                  g_Joy_wrk.readwrite_ofs++;
                }
              }
            }
            break;
          }

          case SEND_EAPPLI_STATE_GC_OPEN_JOY_SIO_CONNECTION:
          {
            if (mJOYSIO_OpenConnection(&g_Joy_wrk) == GBA2_GBA_STATE_SUCCESS) {
              g_Joy_wrk.cmd_stage++;
            }
            else {
              g_Joy_wrk.cmd_attempts = 0;
            }
            break;
          }

          case SEND_EAPPLI_STATE_JOY_SIO_CONNECTION_OPEN:
          {
            int attempt;
            for (attempt = 0; attempt < 24; attempt++) {
              int res = mGcgba_IsTypes(&g_Joy_wrk, 0xFFFE020A, 0xCDCDCDCD);
              if (res != GBA2_GBA_STATE_TRANSMITTING) {
                if (res == GBA2_GBA_STATE_SUCCESS) {
                  gba_state = GBA2_EAPPLI_SUCCESS;
                }
                else {
                  gba_state = GBA2_EAPPLI_FAILURE_NO_GBA;
                }
                break;
              }
            }
            break;
          }
        }
      }
      else {
        gba_state = GBA2_EAPPLI_FAILURE_NO_GBA;
      }
    }
    else {
      gba_state = GBA2_EAPPLI_FAILURE_NO_GBA;
    }
  }

  if (gba_state == GBA2_EAPPLI_FAILURE_NO_GBA && g_Joy_wrk.cmd_stage != 0) {
    gba_state = GBA2_EAPPLI_FAILURE_XFER_ERROR;
  }

  return gba_state;
}
